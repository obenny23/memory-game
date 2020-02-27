#include "SPI.h"
#include "SysTimer.h"

// Note: When the data frame size is 8 bit, "SPIx->DR = byte_data;" works incorrectly. 
// It mistakenly send two bytes out because SPIx->DR has 16 bits. To solve the program,
// we should use "*((volatile uint8_t*)&SPIx->DR) = byte_data";


// LSM303C eCompass (a 3D accelerometer and 3D magnetometer module) SPI Interface: 
//   MAG_DRDY = PC2   MEMS_SCK  = PD1 (SPI2_SCK)   XL_CS  = PE0             
//   MAG_CS   = PC0   MEMS_MOSI = PD4 (SPI2_MOSI)  XL_INT = PE1       
//   MAG_INT  = PC1 
//
// L3GD20 Gyro (three-axis digital output) SPI Interface: 
//   MEMS_SCK  = PD1 (SPI2_SCK)    GYRO_CS   = PD7 (GPIO)
//   MEMS_MOSI = PD4 (SPI2_MOSI)   GYRO_INT1 = PD2
//   MEMS_MISO = PD3 (SPI2_MISO)   GYRO_INT2 = PB8

extern uint8_t Rx1_Counter;
extern uint8_t Rx2_Counter;

void SPI2_GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
	//PD1 setup
	GPIOD->MODER &=~ GPIO_MODER_MODE1;
	GPIOD->MODER |= GPIO_MODER_MODE1_1;
	GPIOD->AFR[0] &=~ GPIO_AFRL_AFRL1;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL1_0 | GPIO_AFRL_AFSEL1_2;
	GPIOD->OTYPER &=~ GPIO_OTYPER_OT1;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1;
	GPIOD->PUPDR &=~ GPIO_PUPDR_PUPD1;
	
	//PD3 setup
	GPIOD->MODER &=~ GPIO_MODER_MODE3;
	GPIOD->MODER |= GPIO_MODER_MODE3_1;
	GPIOD->AFR[0] &=~ GPIO_AFRL_AFRL3;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL3_0 | GPIO_AFRL_AFSEL3_2;
	GPIOD->OTYPER &=~ GPIO_OTYPER_OT3;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;
	GPIOD->PUPDR &=~ GPIO_PUPDR_PUPD3;
	
	//PD4 setup
	GPIOD->MODER &=~ GPIO_MODER_MODE4;
	GPIOD->MODER |= GPIO_MODER_MODE4_1;
	GPIOD->AFR[0] &=~ GPIO_AFRL_AFRL4;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL4_0 | GPIO_AFRL_AFSEL4_2;
	GPIOD->OTYPER &=~ GPIO_OTYPER_OT4;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;
	GPIOD->PUPDR &=~ GPIO_PUPDR_PUPD4;
}

void SPI_Init(void){
	//1
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_SPI2RST;
	RCC->APB1RSTR1 &=~ RCC_APB1RSTR1_SPI2RST;
	//2
	SPI2->CR1 &=~ SPI_CR1_SPE; 				//disable spi
	//a
	SPI2->CR1 &=~ SPI_CR1_RXONLY;			
	//b
	SPI2->CR1 &=~ SPI_CR1_BIDIMODE;		
	//c
	SPI2->CR1 &=~ SPI_CR1_BIDIOE;			
	//d
	SPI2->CR1 &=~ SPI_CR1_LSBFIRST;
	SPI2->CR2 &=~ SPI_CR2_DS;
	SPI2->CR2 |= SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2; //0111
	SPI2->CR2 &=~ SPI_CR2_FRF;
	//e
	SPI2->CR1 &=~ SPI_CR1_CPOL;
	SPI2->CR1 &=~ SPI_CR1_CPHA;
	//f
	SPI2->CR1 &=~ SPI_CR1_BR;
	SPI2->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1; //011
	//g 
	SPI2->CR1 &=~ SPI_CR1_CRCEN;
	//h
	SPI2->CR1 |= SPI_CR1_MSTR;
	SPI2->CR1 |= SPI_CR1_SSM;
	SPI2->CR2 |= SPI_CR2_NSSP;
	//i
	SPI2->CR1 |= SPI_CR1_SSI;
	//j
	SPI2->CR2 |= SPI_CR2_FRXTH;
	//K
	SPI2->CR1 |= SPI_CR1_SPE;
}
 
void SPI_Write(SPI_TypeDef * SPIx, uint8_t *txBuffer, uint8_t * rxBuffer, int size) {
	volatile uint32_t tmpreg; 
	int i = 0;
	for (i = 0; i < size; i++) {
		while( (SPIx->SR & SPI_SR_TXE ) != SPI_SR_TXE );  // Wait for TXE (Transmit buffer empty)
		*((volatile uint8_t*)&SPIx->DR) = txBuffer[i];
		while((SPIx->SR & SPI_SR_RXNE ) != SPI_SR_RXNE); // Wait for RXNE (Receive buffer not empty)
		rxBuffer[i] = *((__IO uint8_t*)&SPIx->DR);
	}
	while( (SPIx->SR & SPI_SR_BSY) == SPI_SR_BSY ); // Wait for BSY flag cleared
}

void SPI_Read(SPI_TypeDef * SPIx, uint8_t *rxBuffer, int size) {
	int i = 0;
	for (i = 0; i < size; i++) {
		while( (SPIx->SR & SPI_SR_TXE ) != SPI_SR_TXE ); // Wait for TXE (Transmit buffer empty)
		*((volatile uint8_t*)&SPIx->DR) = rxBuffer[i];	
		// The clock is controlled by master. Thus the master has to send a byte
		// data to the slave to start the clock. 
		while((SPIx->SR & SPI_SR_RXNE ) != SPI_SR_RXNE); 
		rxBuffer[i] = *((__IO uint8_t*)&SPIx->DR);
	}
	while( (SPIx->SR & SPI_SR_BSY) == SPI_SR_BSY ); // Wait for BSY flag cleared
}
 

void SPI_Delay(uint32_t us) {
	uint32_t i, j;
	for (i = 0; i < us; i++) {
		for (j = 0; j < 18; j++) // This is an experimental value.
			(void)i;
	}
}

void SPIx_IRQHandler(SPI_TypeDef * SPIx, uint8_t *buffer, uint8_t *counter) {
	if(SPIx->SR & SPI_SR_RXNE) {        //	SPI Busy
		buffer[*counter] = SPIx->DR;   
		// Reading SPI_DR automatically clears the RXNE flag 
		(*counter)++;  
		if( (*counter) >= BufferSize )  {
			(*counter) = 0;
		}  
	}
}

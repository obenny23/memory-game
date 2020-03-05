#include "SPI.h"
#include "SysTimer.h"

// Note: When the data frame size is 8 bit, "SPIx->DR = byte_data;" works incorrectly. 
// It mistakenly send two bytes out because SPIx->DR has 16 bits. To solve the program,
// we should use "*((volatile uint8_t*)&SPIx->DR) = byte_data";

extern uint8_t Rx1_Counter;
extern uint8_t Rx2_Counter;

void SPI1_GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	//PE15 setup DataIn MOSI
	GPIOE->MODER &=~ GPIO_MODER_MODE15;
	GPIOE->MODER |= GPIO_MODER_MODE15_1;
	GPIOE->AFR[1] &=~ GPIO_AFRH_AFSEL15;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL15_0 | GPIO_AFRH_AFSEL15_2;
	GPIOE->OTYPER &=~ GPIO_OTYPER_OT15;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15;
	GPIOE->PUPDR &=~ GPIO_PUPDR_PUPD15;
	
	//PE13 setup CLK
	GPIOE->MODER &=~ GPIO_MODER_MODE13;
	GPIOE->MODER |= GPIO_MODER_MODE13_1;
	GPIOE->AFR[1] &=~ GPIO_AFRH_AFSEL13;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL13_0 | GPIO_AFRH_AFSEL13_2;
	GPIOE->OTYPER &=~ GPIO_OTYPER_OT13;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13;
	GPIOE->PUPDR &=~ GPIO_PUPDR_PUPD13;
	
	//PE12 chip select C
	GPIOE->MODER &=~ GPIO_MODER_MODE12;
	GPIOE->MODER |= GPIO_MODER_MODE12_1;
	GPIOE->AFR[1] &=~ GPIO_AFRH_AFSEL12;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL12_0 | GPIO_AFRH_AFSEL12_2;
	GPIOE->OTYPER &=~ GPIO_OTYPER_OT12;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12;
	GPIOE->PUPDR &=~ GPIO_PUPDR_PUPD12;
}

void SPI_Init(void){
	//1
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
	RCC->APB2RSTR &=~ RCC_APB2RSTR_SPI1RST;
	//2
	SPI1->CR1 &=~ SPI_CR1_SPE; 				//disable spi
	//a
	SPI1->CR1 &=~ SPI_CR1_RXONLY;			
	//b
	SPI1->CR1 &=~ SPI_CR1_BIDIMODE;		
	//c
	SPI1->CR1 &=~ SPI_CR1_BIDIOE;			
	//d
	SPI1->CR1 |= SPI_CR1_LSBFIRST;
	SPI1->CR2 &=~ SPI_CR2_DS;
	SPI1->CR2 |= SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2; //0111
	SPI1->CR2 &=~ SPI_CR2_FRF;
	//e
	SPI1->CR1 &=~ SPI_CR1_CPOL;
	SPI1->CR1 &=~ SPI_CR1_CPHA;
	//f
	SPI1->CR1 &=~ SPI_CR1_BR;
	SPI1->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1; //011
	//g 
	SPI1->CR1 &=~ SPI_CR1_CRCEN;
	//h
	SPI1->CR1 |= SPI_CR1_MSTR;
	SPI1->CR1 |= SPI_CR1_SSM;
	SPI1->CR2 |= SPI_CR2_NSSP;
	//i
	SPI1->CR1 |= SPI_CR1_SSI;
	//
	SPI1->CR2 |= SPI_CR2_FRXTH;
	//K
	SPI1->CR1 |= SPI_CR1_SPE;
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

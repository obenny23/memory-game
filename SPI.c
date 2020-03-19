/*
 * ECE 153B - Winter 2020
 *
 * Names: Benigno Ortega, Javier Jimenez
 * Section: T 7-9:50 
 */ 

#include "SPI.h"
#include "SysTimer.h"


extern uint16_t Rx1_Counter;
extern uint16_t Rx2_Counter;

void SPI1_GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	//PE13 setup CLK
	GPIOE->MODER &=~ GPIO_MODER_MODE13;
	GPIOE->MODER |= GPIO_MODER_MODE13_1;
	GPIOE->AFR[1] &=~ GPIO_AFRH_AFSEL13;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL13_0 | GPIO_AFRH_AFSEL13_2;
	GPIOE->OTYPER &=~ GPIO_OTYPER_OT13;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13;
	GPIOE->PUPDR &=~ GPIO_PUPDR_PUPD13;
	
	//PE12 CS (NSS)
	GPIOE->MODER &=~ GPIO_MODER_MODE12;
	GPIOE->MODER |= GPIO_MODER_MODE12_1;
	GPIOE->AFR[1] &=~ GPIO_AFRH_AFSEL12;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL12_0 | GPIO_AFRH_AFSEL12_2;
	GPIOE->OTYPER &=~ GPIO_OTYPER_OT12;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12;
	GPIOE->PUPDR &=~ GPIO_PUPDR_PUPD12;
	
	//PE14 chip select MISO
	GPIOE->MODER &=~ GPIO_MODER_MODE14;
	GPIOE->MODER |= GPIO_MODER_MODE14_1;
	GPIOE->AFR[1] &=~ GPIO_AFRH_AFSEL14;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL14_0 | GPIO_AFRH_AFSEL14_2;
	GPIOE->OTYPER &=~ GPIO_OTYPER_OT14;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14;
	GPIOE->PUPDR &=~ GPIO_PUPDR_PUPD14;
	
		//PE15 setup DataIn MOSI
	GPIOE->MODER &=~ GPIO_MODER_MODE15;
	GPIOE->MODER |= GPIO_MODER_MODE15_1;
	GPIOE->AFR[1] &=~ GPIO_AFRH_AFSEL15;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL15_0 | GPIO_AFRH_AFSEL15_2;
	GPIOE->OTYPER &=~ GPIO_OTYPER_OT15;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15;
	GPIOE->PUPDR &=~ GPIO_PUPDR_PUPD15;
	
}

void SPI_Init(void){

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;  		// Enable the clock for SPI 1
	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;  	// Reset SP1 1
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST; 	// Clear reset bit
	
	SPI1->CR1 &=~ SPI_CR1_SPE;			// Disable SPI2
	SPI1->CR1 &=~ SPI_CR1_RXONLY;		// Full Duplex Comm
	SPI1->CR1 &=~ SPI_CR1_BIDIMODE;		// Configure 2-line unidir mode
	SPI1->CR1 &=~ SPI_CR1_BIDIOE;		// Disable output in biDir mode
	SPI1->CR1 &=~ SPI_CR1_LSBFIRST;		// MSB first
	SPI1->CR2 |= SPI_CR2_DS;  			// Data length 16 bits 0b1111
	SPI1->CR2 &=~ SPI_CR2_FRF;			// FF Motorola Mode
	SPI1->CR1 &=~ SPI_CR1_CPOL;			// Clock polarity = 0
	SPI1->CR1 &=~ SPI_CR1_CPHA;			// first CLK transition is first data capture edge
	
	// Set the baud rate to 16  0b011
	SPI1->CR1 &=~ SPI_CR1_BR;
	SPI1->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1;
	
	SPI1->CR1 &=~ SPI_CR1_CRCEN;		// Disable CRC calculation
	SPI1->CR1 |= SPI_CR1_MSTR; 			// OP in master mode
	
	// Enable Soft Slave Management and NSSP Management
	SPI1->CR1 |= SPI_CR1_SSM;
	SPI1->CR2 |= SPI_CR2_NSSP;
	
	SPI1->CR1 |= SPI_CR1_SSI;			// Set internal SS bit
	SPI1->CR2 &=~ SPI_CR2_FRXTH; 		// Set FIFO reception threshold to 1/4
	SPI1->CR1 |= SPI_CR1_SPE; 			// Enable SPI1
}
 
void SPI_Write(SPI_TypeDef * SPIx, uint16_t *txBuffer,int size) {
	volatile uint16_t tmpreg; 
	int i = 0;
	for (i = 0; i < size; i++) {
		while( (SPIx->SR & SPI_SR_TXE ) != SPI_SR_TXE );  // Wait for TXE (Transmit buffer empty)
		*((volatile uint16_t*)&SPIx->DR) = txBuffer[i];
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

void SPIx_IRQHandler(SPI_TypeDef * SPIx, uint16_t *buffer, uint16_t *counter) {
	if(SPIx->SR & SPI_SR_RXNE) {        //	SPI Busy
		buffer[*counter] = SPIx->DR;   
		// Reading SPI_DR automatically clears the RXNE flag 
		(*counter)++;  
		if( (*counter) >= BufferSize )  {
			(*counter) = 0;
		}  
	}
}

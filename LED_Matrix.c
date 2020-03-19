/*
 * ECE 153B - Winter 2020
 *
 * Names: Benigno Ortega, Javier Jimenez
 * Section: T 7-9:50 
 */ 
 
#include "LED_Matrix.h"
#include "SPI.h"

void LED_Matrix_Init(void) {
	//SPI Initialization
	SPI1_GPIO_Init();
	SPI_Init();
	
	//LED Matrix Initialization
	LED_CS_Init();
	initializeLEDMatrix();
	Clear_LED_Matrix();
}


void LED_CS_Init(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	GPIOE->MODER &=~ GPIO_MODER_MODE10;
	GPIOE->MODER |= GPIO_MODER_MODE10_0;
	GPIOE->OTYPER &=~ GPIO_OTYPER_OT10;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10;
	GPIOE->PUPDR &=~ GPIO_PUPDR_PUPD10;
}


void Clear_LED_Matrix(void){
	uint16_t clear1 = 0b0000000100000000;
	uint16_t clear2 = 0b0000001000000000;
	uint16_t clear3 = 0b0000001100000000;
	uint16_t clear4 = 0b0000010000000000;
	uint16_t clear5 = 0b0000010100000000;
	uint16_t clear6 = 0b0000011000000000;
	uint16_t clear7 = 0b0000011100000000;
	uint16_t clear8 = 0b0000100000000000;
	
	
	LED_CS_LOW;
	SPI_Write(SPI1, &clear1,1);
	SPI_Write(SPI1, &clear1,1);
	SPI_Write(SPI1, &clear1,1);
	SPI_Write(SPI1, &clear1,1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &clear2,1);
	SPI_Write(SPI1, &clear2,1);
	SPI_Write(SPI1, &clear2,1);
	SPI_Write(SPI1, &clear2,1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &clear3,1);
	SPI_Write(SPI1, &clear3,1);
	SPI_Write(SPI1, &clear3,1);
	SPI_Write(SPI1, &clear3,1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &clear4,1);
	SPI_Write(SPI1, &clear4,1);
	SPI_Write(SPI1, &clear4,1);
	SPI_Write(SPI1, &clear4,1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &clear5,1);
	SPI_Write(SPI1, &clear5,1);
	SPI_Write(SPI1, &clear5,1);
	SPI_Write(SPI1, &clear5,1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &clear6,1);
	SPI_Write(SPI1, &clear6,1);
	SPI_Write(SPI1, &clear6,1);
	SPI_Write(SPI1, &clear6,1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &clear7,1);
	SPI_Write(SPI1, &clear7,1);
	SPI_Write(SPI1, &clear7,1);
	SPI_Write(SPI1, &clear7,1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &clear8,1);
	SPI_Write(SPI1, &clear8,1);
	SPI_Write(SPI1, &clear8,1);
	SPI_Write(SPI1, &clear8,1);
	LED_CS_HIGH;
}


void initializeLEDMatrix(){
	uint16_t noDecode =  0b0000100100000000;
	uint16_t intensity = 0b0000101000000011;
	uint16_t scanLimit = 0b0000101100000111;
	uint16_t normalMode = 0b0000110000000001;
	uint16_t displayTest = 0b0000111100000000;
	uint16_t shutdown = 0b0000110000000001;	
	
	
	LED_CS_LOW;
	SPI_Write(SPI1,&shutdown,1);
	SPI_Write(SPI1,&shutdown,1);
	SPI_Write(SPI1,&shutdown,1);
	SPI_Write(SPI1,&shutdown,1);
	LED_CS_HIGH;
	
  	LED_CS_LOW;
	SPI_Write(SPI1, &noDecode, 1);
	SPI_Write(SPI1, &noDecode, 1);
	SPI_Write(SPI1, &noDecode, 1);
	SPI_Write(SPI1, &noDecode, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &intensity, 1);
	SPI_Write(SPI1, &intensity, 1);
	SPI_Write(SPI1, &intensity, 1);
	SPI_Write(SPI1, &intensity, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &scanLimit, 1);
	SPI_Write(SPI1, &scanLimit, 1);
	SPI_Write(SPI1, &scanLimit, 1);
	SPI_Write(SPI1, &scanLimit, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &normalMode, 1);
	SPI_Write(SPI1, &normalMode, 1);
	SPI_Write(SPI1, &normalMode, 1);
	SPI_Write(SPI1, &normalMode, 1);
	LED_CS_HIGH;
}


void DisplayPlayer(int p){
	uint16_t noop = 0b0000000000000000;
	uint16_t fM1, fM2, fM3, fM4, fM5, fM6, fM7, fM8;
	
	if (p == 1) {
		fM1 = 0b0000000111100001;
		fM2 = 0b0000001001000001;
		fM3 = 0b0000001101000001;
		fM4 = 0b0000010001000001;
		fM5 = 0b0000010101000111;
		fM6 = 0b0000011001001001;
		fM7 = 0b0000011101101001;
		fM8 = 0b0000100001000111;
	}
	
	else if (p == 2) {
		fM1 = 0b0000000111110001;
		fM2 = 0b0000001000010001;
		fM3 = 0b0000001100100001;
		fM4 = 0b0000010001000001;
		fM5 = 0b0000010110000111;
		fM6 = 0b0000011010001001;
		fM7 = 0b0000011110001001;
		fM8 = 0b0000100001110111;
	}
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM1, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM2, 1);
	LED_CS_HIGH;
	

	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM3, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM4, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM5, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM6, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM7, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM8, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	LED_CS_HIGH;
}

void Sad(void) {
	uint16_t noop = 0b0000000000000000;
	uint16_t fM1 = 0b0000000110000001;
	uint16_t fM2 = 0b0000001010000001;
	uint16_t fM3 = 0b0000001101000010;
	uint16_t fM4 = 0b0000010000111100;
	uint16_t fM5 = 0b0000010100000000;
	uint16_t fM6 = 0b0000011000100100;
	uint16_t fM7 = 0b0000011100100100;
	uint16_t fM8 = 0b0000100000000000;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM1, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM2, 1);
	LED_CS_HIGH;
	

	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM3, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM4, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM5, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM6, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM7, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM8, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	LED_CS_HIGH;
}
	

void Happy(void) {
	uint16_t noop = 0b0000000000000000;
	
	uint16_t fM1 = 0b0000000100111100;
	uint16_t fM2 = 0b0000001001000010;
	uint16_t fM3 = 0b0000001110000001;
	uint16_t fM4 = 0b0000010010000001;
	uint16_t fM5 = 0b0000010100000000;
	uint16_t fM6 = 0b0000011000100100;
	uint16_t fM7 = 0b0000011100100100;
	uint16_t fM8 = 0b0000100000000000;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM1, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM2, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM3, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM4, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM5, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM6, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM7, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM8, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	LED_CS_HIGH;
}
void DisplayArrows(void) {
	uint16_t noop = 0b0000000000000000;
	
	uint16_t fM8 = 0b0000100000111000;
	uint16_t fM7 = 0b0000011100111000;
	uint16_t fM6 = 0b0000011000111000;
	uint16_t fM5 = 0b0000010100111000;
	uint16_t fM4 = 0b0000010011111110;
	uint16_t fM3 = 0b0000001101111100;
	uint16_t fM2 = 0b0000001000111000;
	uint16_t fM1 = 0b0000000100010000;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM1, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM2, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM3, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM4, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM5, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM6, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM7, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM8, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	LED_CS_HIGH;
}

void QuestionMark(void) {
  uint16_t noop = 0b0000000000000000;
	
	uint16_t fM8 = 0b0000100000111100;
	uint16_t fM7 = 0b0000011101100110;
	uint16_t fM6 = 0b0000011001100110;
	uint16_t fM5 = 0b0000010100110000;
	uint16_t fM4 = 0b0000010000011000;
	uint16_t fM3 = 0b0000001100000000;
	uint16_t fM2 = 0b0000001000011000;
	uint16_t fM1 = 0b0000000100011000;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM1, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM2, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM3, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM4, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM5, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM6, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM7, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM8, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	LED_CS_HIGH;
}

void AddPattern(void) {
	uint16_t noop = 0b0000000000000000;
	
	uint16_t fM8 = 0b0000100000000000;
	uint16_t fM7 = 0b0000011100011000;
	uint16_t fM6 = 0b0000011000011000;
	uint16_t fM5 = 0b0000010101111110;
	uint16_t fM4 = 0b0000010001111110;
	uint16_t fM3 = 0b0000001100011000;
	uint16_t fM2 = 0b0000001000011000;
	uint16_t fM1 = 0b0000000100000000;
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM1, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM2, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM3, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM4, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM5, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM6, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM7, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM8, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	LED_CS_HIGH;
}


void Difficulty(void) {
	uint16_t noop = 0b0000000000000000;
	
	uint16_t fM8 = 0b0000100000000001;
	uint16_t fM7 = 0b0000011100001101;
	uint16_t fM6 = 0b0000011000010001;
	uint16_t fM5 = 0b0000010101101001;
	uint16_t fM4 = 0b0000010010011100;
	uint16_t fM3 = 0b0000001101000000;
	uint16_t fM2 = 0b0000001010000000;
	uint16_t fM1 = 0b0000000101100000;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM1, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM2, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM3, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM4, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM5, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM6, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM7, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM8, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	LED_CS_HIGH;
}


void Game_Over_Display(void) {
	uint16_t noop = 0b0000000000000000;
	
	uint16_t fM1 = 0b0000000111111111;
	uint16_t fM2 = 0b0000001011111111;
	uint16_t fM3 = 0b0000001111111111;
	uint16_t fM4 = 0b0000010011111111;
	uint16_t fM5 = 0b0000010111111111;
	uint16_t fM6 = 0b0000011011111111;
	uint16_t fM7 = 0b0000011111111111;
	uint16_t fM8 = 0b0000100011111111;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM1, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM2, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM3, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM4, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM5, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM6, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM7, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &fM8, 1);
	LED_CS_HIGH;
	
	LED_CS_LOW;
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	SPI_Write(SPI1, &noop, 1);
	LED_CS_HIGH;	
}

	
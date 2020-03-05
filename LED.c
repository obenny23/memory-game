#include "LED.h"

void LED_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;	
	
	// Initialize PB2 LED *UP
	GPIOB->MODER &=~ GPIO_MODER_MODE3;
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	GPIOB->OTYPER &=~ GPIO_OTYPER_OT3;
  GPIOB->PUPDR &=~ GPIO_PUPDR_PUPDR3;
	
	// Initialize PA3 LED *DOWN
	GPIOA->MODER &=~ GPIO_MODER_MODE2;
  GPIOA->MODER |= GPIO_MODER_MODE2_0;
  GPIOA->OTYPER &=~ GPIO_OTYPER_OT2;
  GPIOA->PUPDR &=~ GPIO_PUPDR_PUPDR2;
	
	// Initialize PB6 LED *LEFT
	GPIOB->MODER &=~ GPIO_MODER_MODE6;
	GPIOB->MODER |= GPIO_MODER_MODE6_0;
	GPIOB->OTYPER &=~ GPIO_OTYPER_OT6;
  GPIOB->PUPDR &=~ GPIO_PUPDR_PUPDR6;
	
	// Initialize PB7 LED *RIGHT
	GPIOB->MODER &=~ GPIO_MODER_MODE7;
	GPIOB->MODER |= GPIO_MODER_MODE7_0;
	GPIOB->OTYPER &=~ GPIO_OTYPER_OT7;
  GPIOB->PUPDR &=~ GPIO_PUPDR_PUPDR7;
}

void PB3_LED_Toggle(void) {
	GPIOB->ODR ^= GPIO_ODR_OD3;
}

void PA2_LED_Toggle(void) {
	GPIOA->ODR ^= GPIO_ODR_OD2;
}

void PB6_LED_Toggle(void) {
	GPIOB->ODR ^= GPIO_ODR_OD6;
}

void PB7_LED_Toggle(void) {
	GPIOB->ODR ^= GPIO_ODR_OD7;
}

void All_LED_Toggle(void){
	PB3_LED_Toggle();
	PA2_LED_Toggle();
	PB6_LED_Toggle();
	PB7_LED_Toggle();
}
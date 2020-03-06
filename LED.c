#include "LED.h"

void LED_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;	
	
	// Initialize PB3 LED *UP
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

void Yellow_LED_Toggle(void) {
	GPIOB->ODR ^= GPIO_ODR_OD3;
}

void Red_LED_Toggle(void) {
	GPIOA->ODR ^= GPIO_ODR_OD2;
}

void Blue_LED_Toggle(void) {
	GPIOB->ODR ^= GPIO_ODR_OD6;
}

void Green_LED_Toggle(void) {
	GPIOB->ODR ^= GPIO_ODR_OD7;
}

void Flash_All_LED(void){
	Yellow_LED_Toggle();
	Red_LED_Toggle();
	Blue_LED_Toggle();
	Green_LED_Toggle();
	for (int i = 0; i < 4000000; i++);
	Yellow_LED_Toggle();
	Red_LED_Toggle();
	Blue_LED_Toggle();
	Green_LED_Toggle();
}
void Flash_Yellow_LED(void){
	Yellow_LED_Toggle();
	for (int i = 0; i < 4000000; i++);
	Yellow_LED_Toggle();
}

void Flash_Red_LED(void){
	Red_LED_Toggle();
	for (int i = 0; i < 4000000; i++);
	Red_LED_Toggle();
}
void Flash_Blue_LED(void){
	Blue_LED_Toggle();
	for (int i = 0; i < 4000000; i++);
	Blue_LED_Toggle();
}
void Flash_Green_LED(void){
	Green_LED_Toggle();
	for (int i = 0; i < 4000000; i++);
	Green_LED_Toggle();
}

void Game_Over_Pattern(void){
	Yellow_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Red_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Blue_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Green_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Yellow_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Red_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Blue_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Green_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Green_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Blue_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Red_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Yellow_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Green_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Blue_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Red_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
	Yellow_LED_Toggle();
	for (int i = 0; i < 1000000; i++);
}

void Game_Over(void){
	Game_Over_Pattern();
	Game_Over_Pattern();
	Flash_All_LED();
	for (int i = 0; i < 800000; i++);
	Flash_All_LED();
	for (int i = 0; i < 800000; i++);
	Flash_All_LED();
	for (int i = 0; i < 800000; i++);
	/*
	Flash_All_LED();
	for (int i = 0; i < 1000000; i++);
	Flash_All_LED();
	for (int i = 0; i < 1000000; i++);
	Flash_All_LED();
	*/
}


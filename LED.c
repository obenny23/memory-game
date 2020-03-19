/*
 * ECE 153B - Winter 2020
 *
 * Names: Benigno Ortega, Javier Jimenez
 * Section: T 7-9:50 
 */

#include "LED.h"
#include "LED_Matrix.h"

void LED_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;	

		// Initialize PA5  *Yellow LED
	GPIOA->MODER &=~ GPIO_MODER_MODE5;
  	GPIOA->MODER |= GPIO_MODER_MODE5_0;
  	GPIOA->OTYPER &=~ GPIO_OTYPER_OT5;
  	GPIOA->PUPDR &=~ GPIO_PUPDR_PUPDR5;

	// Initialize PA1 *Red LED
	GPIOA->MODER &=~ GPIO_MODER_MODE1;
	GPIOA->MODER |= GPIO_MODER_MODE1_0;
	GPIOA->OTYPER &=~ GPIO_OTYPER_OT1;
  	GPIOA->PUPDR &=~ GPIO_PUPDR_PUPDR1;

	// Initialize PA2 *Blue LED
	GPIOA->MODER &=~ GPIO_MODER_MODE2;
	GPIOA->MODER |= GPIO_MODER_MODE2_0;
	GPIOA->OTYPER &=~ GPIO_OTYPER_OT2;
  	GPIOA->PUPDR &=~ GPIO_PUPDR_PUPDR2;	

	// Initialize PA3 *Green LED
	GPIOA->MODER &=~ GPIO_MODER_MODE3;
	GPIOA->MODER |= GPIO_MODER_MODE3_0;
	GPIOA->OTYPER &=~ GPIO_OTYPER_OT3;
  	GPIOA->PUPDR &=~ GPIO_PUPDR_PUPDR3;
}


void Yellow_LED_Toggle(void) {
	GPIOA->ODR ^= GPIO_ODR_OD5;
}

void Red_LED_Toggle(void) {
	GPIOA->ODR ^= GPIO_ODR_OD1;
}

void Blue_LED_Toggle(void) {
	GPIOA->ODR ^= GPIO_ODR_OD2;
}

void Green_LED_Toggle(void) {
	GPIOA->ODR ^= GPIO_ODR_OD3;
}

void Flash_All_LED(void){

	Yellow_LED_Toggle();
	Red_LED_Toggle();
	Blue_LED_Toggle();
	Green_LED_Toggle();

	led_delay(4000000);

	Yellow_LED_Toggle();
	Red_LED_Toggle();
	Blue_LED_Toggle();
	Green_LED_Toggle();
}

void Flash_Yellow_LED(void){
	Yellow_LED_Toggle();
	led_delay(4000000);
	Yellow_LED_Toggle();
}

void Flash_Red_LED(void){
	Red_LED_Toggle();
	led_delay(4000000);
	Red_LED_Toggle();
}

void Flash_Blue_LED(void){
	Blue_LED_Toggle();
	led_delay(4000000);
	Blue_LED_Toggle();
}

void Flash_Green_LED(void){
	Green_LED_Toggle();
	led_delay(4000000);
	Green_LED_Toggle();
}

void Game_Over_Pattern(void){
	Game_Over_Display();
	Yellow_LED_Toggle();
	led_delay(1000000);
	Red_LED_Toggle();
	led_delay(1000000);
	Blue_LED_Toggle();
	led_delay(1000000);
	Green_LED_Toggle();
	led_delay(1000000);
	Yellow_LED_Toggle();
	led_delay(1000000);
	Red_LED_Toggle();
	led_delay(1000000);
	Blue_LED_Toggle();
	led_delay(1000000);
	Green_LED_Toggle();
	led_delay(1000000);
	Clear_LED_Matrix();
	Green_LED_Toggle();
	led_delay(1000000);
	Blue_LED_Toggle();
	led_delay(1000000);
	Red_LED_Toggle();
	led_delay(1000000);
	Yellow_LED_Toggle();
	led_delay(1000000);
	Green_LED_Toggle();
	led_delay(1000000);
	Blue_LED_Toggle();
	led_delay(1000000);
	Red_LED_Toggle();
	led_delay(1000000);
	Yellow_LED_Toggle();
	led_delay(1000000);
}


void Game_Over(void){
	Game_Over_Pattern();
	Game_Over_Pattern();
	
	Game_Over_Display();
	Flash_All_LED();
	led_delay(800000);
	Clear_LED_Matrix();
	Flash_All_LED();
	led_delay(800000);
	Game_Over_Display();
	Flash_All_LED();
  	led_delay(800000);
	Clear_LED_Matrix();
}

void led_delay(int x) {	for (int i = 0; i < x; i++);	}

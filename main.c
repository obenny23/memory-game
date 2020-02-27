/*
 * ECE 153B - Winter 2020
 *
 * Name(s): Benigno Ortega, Javier
 * Section: T 7-9:50 
 * Lab: 1A
 */

#include "stm32l476xx.h"
#include "LED.h"
#include "LED_Display.h"
#include "UART.h"
#include "SysClock.h"


int main() {
	
	UART1_Init();
	UART1_GPIO_Init();
	USART_Init(USART1);
	System_Clock_Init();
	LED_Init();
	
	
	// Initialization
	char *arr[] = { "1000", "0100","0010","0001", "0001", "0001", "0001", "1000", "0010", "0100", "0010", "0001", "1000", "0100" };
	
	// Polling to Check for Button Presses
	Display_Pattern(arr);
}

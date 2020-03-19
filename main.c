/*
 * ECE 153B - Winter 2020
 *
 * Names: Benigno Ortega, Javier Jimenez
 * Section: T 7-9:50 
 */

#include "stm32l476xx.h"
#include "LED.h"
#include "LED_Display.h"
#include "UART.h"
#include "SysClock.h"
#include "LED_Matrix.h"
#include "SysTimer.h"
#include "SPI.h"
 
int main() {	
	System_Clock_Init();
	SysTick_Init();
	LED_Init();
	Init_USART();
	LED_Matrix_Init();
		
	Play_Game();
}
	
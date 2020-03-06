/*
 * ECE 153B - Winter 2020
 * Name(s): Benigno Ortega, Javier
 * Section: T 7-9:50 
 */

#include "stm32l476xx.h"
#include "LED.h"
#include "LED_Display.h"
#include "SPI.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "UART.h"
#include "SysClock.h"



int main() {
	System_Clock_Init();
	SysTick_Init();
	LED_Init();
	Init_USARTx(1);
	SPI_Init();
	SPI1_GPIO_Init();
	
	//SPI1->DR = 0x00000303;
  //uint8_t temp = 0x00000303;
	//uint8_t rxBuffer[34];
	//SPI_Write(SPI1, &temp, rxBuffer, 8);

	// Initialization
	char *arr1[]= {0};
	char *arr2[] ={0};	
	int number_of_elements= 3;
	char rxByte;
	bool wrong = false;
	bool player = true;
	//player = false -> player 1
	//player = true -> Player 2
	
	printf("Begin Game!\n\n");
	Game_Over();
	for (int z = 0; z < 1000000; z++);
	//PLAYER 1 starts game with three inputs
	//display player 1 turn on LCD
	printf("Player 1's Turn\n");
	printf("Enter Initial Pattern\n");
	input_colors(arr1,number_of_elements,rxByte);
	

	//PLAYER 2 guesses the input
	while (!wrong){
		//player 2's turn
			if (player) {
				Display_Pattern(arr1, number_of_elements);
				//display "Player 2 Turn"
				printf("Player 2's Turn\n");
				input_colors(arr2,number_of_elements, rxByte);
				//wrong = check_arrays(arr1, arr2, number_of_elements);
				wrong = true;
				if (!wrong) {
					number_of_elements += 1;
					update_Pattern(arr2, number_of_elements, rxByte);
				}
				player = false;
			}
			//Player 1's turn
			else if (!player) {
				Display_Pattern(arr2, number_of_elements);
				printf("Player 1 Turn");
				input_colors(arr1, number_of_elements, rxByte);
				wrong = check_arrays(arr1, arr2, number_of_elements);
				if (!wrong) {
					number_of_elements += 1;
					update_Pattern(arr1, number_of_elements, rxByte);
				}
				player = true;
			}
	}
	
	if (wrong) {
			if (player) {
				Game_Over();
				printf("GAMEOVER, Player 1 Wins");
			}	
			else if (!player) {
				Game_Over();
				printf("GAMEOVER, Player 2 Wins");
			}
	}
}


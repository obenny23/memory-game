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
#include <stdbool.h>
#include "UART.h"
#include "SysClock.h"
#include <string.h>
#include <stdio.h>

bool check_arrays(char *arr1, char*arr2,int num){
	printf("INSIDE COMPARATOR");
	bool result = true;
	for(int i = 0; i<num;i++){
		if(!strcmp(arr1[i],arr2[i])){
			char*a = arr1[i];
			char*b= arr2[i];
			printf(a);
			printf("/n");
			printf(b);
				continue;
		}else{
			result = false;
		 char*a = arr1[i];
			char*b= arr2[i];
			
			
		 printf(a);
			printf("/n");
			printf(b);
			
		}
	}
	return result;
}

void input_colors(char*arr3[], int num_of_elements,char rxByte){
	printf("SCANNING");
	for(int k = 0; k < num_of_elements + 1 ; k++){
		scanf("%c",&rxByte);
		
		if(rxByte == 'y'){
			arr3[k]= "0001";
		}
		if(rxByte == 'g'){
			arr3[k] = "1000";
	}
		if(rxByte == 'r'){
			arr3[k] = "0100";
		}
		if(rxByte == 'b'){
			arr3[k] = "0010";
		}
	}
}
	
int main() {
	System_Clock_Init();
	SysTick_Init();
	
	//UART2_Init();
	//UART2_GPIO_Init();
	//USART_Init(USART2);
	
	//LED_Init();
	SPI_Init();
	SPI1_GPIO_Init();
	
	SPI1->DR = 0x00000303;
  uint8_t temp = 0x00000303;
	
	uint8_t rxBuffer[34];
	
	SPI_Write(SPI1, &temp, rxBuffer, 8);
	/*
	char *arr[] = { "1000", "0100","0010","0001", "0001", "0001", "0001", "1000", "0010", "0100", "0010", "0001", "1000", "0100" };
	Display_Pattern(arr, 13);
	/*
	// Initialization
	char *arr1[]= {0};
	char *arr2[] ={0};
	int index;
	int number_of_elements= 2;
	
	char rxByte;
	
	
	printf("Enter a command");
	//PLAYER 1 starts game with three inputs
	input_colors(arr1,number_of_elements,rxByte);
	//number_of_elements = number_of_elements + 1;
	Display_Pattern(arr1,number_of_elements+1);
	
	//PLAYER 2 guesses the input
	input_colors(arr2,number_of_elements, rxByte);
	Display_Pattern(arr2,number_of_elements+1);
	bool final = check_arrays(arr1,arr2,number_of_elements+1);
	if(final == false){
		printf("GAMEOVER");
	}else{
		printf("WIN");
	}
	*/
}

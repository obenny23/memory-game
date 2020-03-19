/*
 * ECE 153B - Winter 2020
 *
 * Names: Benigno Ortega, Javier Jimenez
 * Section: T 7-9:50 
 */ 
 
#include "LED_Display.h"
#include "LED_Matrix.h"
#include "LED.h"


bool check_arrays(char arr1[], char arr2[],int num){
	bool result = true;
	for(int i = 0; i < num ; i++){
		if(arr1[i] == arr2[i]){	} //Do Nothing

		else if (arr1[i]!=arr2[i]){		
			result = false;
		}		 
	}
	return result;
}


void input_colors(char arr3[], int num_of_elements,char rxByte){
	bool valid = false;

	for(int k = 0; k < num_of_elements  ; k++){
		scanf("%c",&rxByte);
		if(rxByte == '1'){
			arr3[k]= 'y';
			Flash_Yellow_LED();
		}
		
		else if(rxByte == '2'){
			arr3[k] = 'r';
			Flash_Red_LED();
		}

		else if(rxByte == '3'){
			arr3[k] = 'b';
			Flash_Blue_LED();
		}

		else if(rxByte == '4'){
			arr3[k] = 'g';
			Flash_Green_LED();
		}

		else {
			while(!valid) {
				printf("Put valid Input\n");
				scanf("%c", &rxByte);

				if(rxByte == '1'){
					arr3[k]= 'y';
					Flash_Yellow_LED();
					valid = true;
				}

				else if(rxByte == '2'){
					arr3[k] = 'r';
					Flash_Red_LED();
					valid = true;
				}

				else if(rxByte == '3'){
					arr3[k] = 'b';
					Flash_Blue_LED();
					valid = true;
				}

				else if(rxByte == '4'){
					arr3[k] = 'g';
					Flash_Green_LED();
					valid = true;
				}			
				
				else { valid = false; }
			}
		}
	}
}



void update_Pattern( char arr[], int num, char rxByte) {

	printf("Correct! Add To Pattern \n");
	scanf("%c",&rxByte);	

	if (rxByte == '1'){
		arr[num-1]= 'y';
		Flash_Yellow_LED();
	}

	if(rxByte == '2'){
		arr[num-1] = 'r';
		Flash_Red_LED();
	}

	if(rxByte == '3'){
		arr[num-1] = 'b';
		Flash_Blue_LED();
	}

	if(rxByte == '4'){
		arr[num-1] = 'g';
		Flash_Green_LED();
	}
}

void Display_Pattern(char arr[], int num, int difficulty){

	for (int z = 0; z < 100000; z++);
	printf("Pay CLOSE Attention!\n");
	for (int z = 0; z < 1000000; z++);		

	for(int i = 0; i < num; i++){
			
			if( arr[i] == 'y'){
				Flash_Yellow_LED();
			}

			if( arr[i] == 'r' ){
				Flash_Red_LED();
			}

			if( arr[i] == 'b'){
				Flash_Blue_LED();
			}

			if( arr[i] == 'g'){
				Flash_Green_LED();
			}
			for(int j = 0; j< difficulty; j++){}
	}	
}

void Play_Game(void){
	char rxByte;
	int speed;

	// Initialization
	printf("Begin Game!\n\n");
	Happy();
	for (int i = 0; i < 10000000; i++){}
	Clear_LED_Matrix();
	for (int i = 0; i < 4000000; i++){}
	Happy();
	for (int i = 0; i < 10000000; i++){}	
 
	bool play = true;
	
	while(play) {
		
		Difficulty();
		printf("Choose Difficulty\n");
		printf("1 = Easy (Default), 2 = Medium, 3 = Hard\n");
		scanf("%c", &rxByte);
		
		if (rxByte == '1') {		speed = 10000000;   }
		else if (rxByte == '2') {  	speed = 3000000; 	 }
		else if (rxByte == '3') { 	speed = 600000;	 }
		else { speed = 10000000;	}
	
		char arr1[50] = {0};  //inputs for player 1
		char arr2[50] ={0};   //inputs for player 2
	 
		int number_of_elements= 3;
		bool correct = true;

		//player = false -> player 1
		//player = true -> Player 2
		bool player = true;

		//PLAYER 1 starts game with three inputs

		//display player 1 turn on LCD

		printf("Player 1's Turn\n");
		DisplayPlayer(1);

		printf("Enter Initial Pattern\n");
		input_colors(arr1,number_of_elements,rxByte);
		
		//PLAYER 2 guesses the input
		while (correct){		
			//player 2's turn
			if (player) {
				DisplayArrows();
				Display_Pattern(arr1, number_of_elements, speed);				
				printf("Player 2's Turn\n");
				DisplayPlayer(2);

				input_colors(arr2,number_of_elements, rxByte);
				correct = (check_arrays(arr1, arr2, number_of_elements)); // if correct returns true

				if (correct) {
					number_of_elements += 1;
					AddPattern();
					update_Pattern(arr2, number_of_elements, rxByte);
					player = false;
				}
			}

			//Player 1's turn
			else if (!player) {
				DisplayArrows();
				Display_Pattern(arr2, number_of_elements, speed);
				printf("Player 1 Turn\n");
				DisplayPlayer(1);

				input_colors(arr1, number_of_elements, rxByte);
				correct = check_arrays(arr1, arr2, number_of_elements);

				if (correct) {
					number_of_elements += 1;
					AddPattern();
					update_Pattern(arr1, number_of_elements, rxByte);
					player = true;
				}
			}
		}

		if (!correct) {
			
			if (player) {
				printf("Game Over \nPlayer 1 Wins\n");
			}	
			else if (!player) {
				printf("Game Over \nPlayer 2 Wins\n");
			}
			Game_Over();
				
			printf("Play Again? y/n \n");
			QuestionMark();
			scanf("%c",&rxByte);
			if (rxByte == 'y') {
				play = true;
				Happy();
				for (int i = 0; i < 8000000; i++){}
			}else {
				play = false;
				printf("Bye!");
				Sad();
			}
		}
	}
	for (int i = 0; i < 10000000; i++);
	Clear_LED_Matrix();
}


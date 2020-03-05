#include "LED_Display.h"
#include "LED.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
/*
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
*/
void Display_Pattern(char* arr[], int num){
		
	for(int i = 0; i<num; i++){
			
			if( !strcmp(arr[i], "1000")){
				PB3_LED_Toggle();
				for(int x = 0; x<10000000; x++){}
				PB3_LED_Toggle();
			}
			
			if( !strcmp(arr[i],"0100") ){
				PA2_LED_Toggle();	
				for(int x = 0; x<10000000; x++){}
				PA2_LED_Toggle();
			}
				
			if( !strcmp(arr[i],"0010")){
				PB6_LED_Toggle();	
				for(int x = 0; x<10000000; x++){}
				PB6_LED_Toggle();
			}
			if( !strcmp(arr[i],"0001" )){
				PB7_LED_Toggle();
				for(int x = 0; x<10000000; x++){}
				PB7_LED_Toggle();
			}
			for(int j = 0; j<10000000;j++){}
	}	
}
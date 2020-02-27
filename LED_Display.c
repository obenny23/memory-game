#include "LED_Display.h"
#include "LED.h"

void Display_Pattern(char* arr[]){
	int count = 0;
	for (int k = 0; k < 50; k++){
		if ( arr[k] != '\0'){
			count++;
		}
	}
		
	for(int i = 0; i<count; i++){
		
			if( !strcmp(arr[i], "1000")){
				PB2_LED_Toggle();
				for(int x = 0; x<1000000; x++){}
				PB2_LED_Toggle();
			}
			
			if( !strcmp(arr[i],"0100") ){
				PA2_LED_Toggle();	
				for(int x = 0; x<1000000; x++){}
				PA2_LED_Toggle();
			}
				
			if( !strcmp(arr[i],"0010")){
				PB6_LED_Toggle();	
				for(int x = 0; x<1000000; x++){}
				PB6_LED_Toggle();
			}
			if( !strcmp(arr[i],"0001" )){
				PB7_LED_Toggle();
				for(int x = 0; x<1000000; x++){}
				PB7_LED_Toggle();
			}
			for(int j = 0; j<1000000;j++){}
	}	
}

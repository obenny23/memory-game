#include "LED_Display.h"
#include "LED.h"

bool check_arrays(char *arr1, char*arr2,int num){

	bool result = true;
	for(int i = 0; i < num ; i++){
		if(!strcmp(arr1[i],arr2[i])){
			char a = arr1[i];
			char b = arr2[i];
			printf("%c ", &a);
			printf("%c ", &b);
			continue;
		}
		else{
			result = false;
			char a = arr1[i];
			char b= arr2[i];
		  printf(a);
			printf("/n");
			printf(b);
		}
	}
	return result;
}

void input_colors(char*arr3[], int num_of_elements,char rxByte){
	bool valid = false;
	for(int k = 0; k < num_of_elements  ; k++){
		scanf("%c",&rxByte);
		if(rxByte == 'y'){
			arr3[k]= "1000";
			Flash_Yellow_LED();
		}
		else if(rxByte == 'r'){
			arr3[k] = "0100";
			Flash_Red_LED();
		}
		else if(rxByte == 'b'){
			arr3[k] = "0010";
			Flash_Blue_LED();
		}
		else if(rxByte == 'g'){
			arr3[k] = "0001";
			Flash_Green_LED();
		}
		else {
			while(!valid) {
				printf("Put valid Input");
				scanf("%c", &rxByte);
				
				if(rxByte == 'y'){
					arr3[k]= "1000";
					Flash_Yellow_LED();
					valid = true;
				}
				else if(rxByte == 'r'){
					arr3[k] = "0100";
					Flash_Red_LED();
					valid = true;
				}
				else if(rxByte == 'b'){
					arr3[k] = "0010";
					Flash_Blue_LED();
					valid = true;
				}
				else if(rxByte == 'g'){
					arr3[k] = "0001";
					Flash_Green_LED();
					valid = true;
				}
				
				else { valid = false; }
			}
		}
	}
}

void update_Pattern( char* arr[], int num, char rxByte) {
	printf("Add To Pattern");
	scanf("%c",&rxByte);
	
	if (rxByte == 'y'){
		arr[num-1]= "1000";
	}
	if(rxByte == 'r'){
		arr[num-1] = "0100";
	}
	if(rxByte == 'b'){
		arr[num-1] = "0010";
	}
	if(rxByte == 'g'){
		arr[num-1] = "0001";
	}
}
void Display_Pattern(char* arr[], int num){
	for (int z = 0; z < 1000000; z++);
	printf("Pay CLOSE Attention!\n");
	for (int z = 0; z < 10000000; z++);
		
	for(int i = 0; i < num; i++){
			//yellow
			if( !strcmp(arr[i], "1000")){
				Yellow_LED_Toggle();
				for(int x = 0; x<8000000; x++){}
				Yellow_LED_Toggle();
			}
			//red
			if( !strcmp(arr[i],"0100") ){
				Red_LED_Toggle();
				for(int x = 0; x<8000000; x++){}
				Red_LED_Toggle();
			}
				//blue
			if( !strcmp(arr[i],"0010")){
				Blue_LED_Toggle();	
				for(int x = 0; x<8000000; x++){}
				Blue_LED_Toggle();
			}
			//green
			if( !strcmp(arr[i],"0001" )){
				Green_LED_Toggle();
				for(int x = 0; x<8000000; x++){}
				Green_LED_Toggle();
			}
			for(int j = 0; j<10000000;j++){}
	}	
}
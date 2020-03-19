#ifndef __STM32L476G_DISCOVERY_LED_DISPLAY_H
#define __STM32L476G_DISCOVERY_LED_DISPLAY_H

#include "stm32l476xx.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


bool check_arrays(char arr1[], char arr2[],int num);
void input_colors(char arr3[], int num_of_elements,char rxByte);
void update_Pattern( char arr[], int num, char rxByte);
void Display_Pattern(char arr[], int num, int difficulty);
void Play_Game(void);

#endif
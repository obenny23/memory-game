#ifndef __STM32L476G_DISCOVERY_LED_MATRIX_H
#define __STM32L476G_DISCOVERY_LED_MATRIX_H

#include "stm32l476xx.h"
#include "UART.h"

#define MULTIPLEBYTE_CMD				((uint8_t)0x40)
#define LED_CS_LOW 				GPIOE->ODR &=~ GPIO_ODR_OD12; 
#define LED_CS_HIGH  			GPIOE->ODR |= GPIO_ODR_OD12;


void LED_Matrix_Init(void);
void LED_CS_Init(void);
void Clear_LED_Matrix(void);
void initializeLEDMatrix(void);
void DisplayPlayer(int p);
void Sad(void);
void Happy(void);
void DisplayArrows(void);
void QuestionMark(void);
void AddPattern(void);
void Difficulty(void);
void Game_Over_Display(void);


#endif

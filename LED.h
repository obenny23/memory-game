#ifndef __STM32L476G_DISCOVERY_LED_H
#define __STM32L476G_DISCOVERY_LED_H

#include "stm32l476xx.h"

void LED_Init(void);

void Yellow_LED_Toggle(void);
void Red_LED_Toggle(void);
void Blue_LED_Toggle(void);
void Green_LED_Toggle(void);

void Flash_All_LED(void);
void Flash_Yellow_LED(void);
void Flash_Red_LED(void);
void Flash_Blue_LED(void);
void Flash_Green_LED(void);

void Game_Over_Pattern(void);
void Game_Over(void);

void led_delay(int x);


#endif

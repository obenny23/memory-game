#ifndef __STM32L476G_DISCOVERY_LED_H
#define __STM32L476G_DISCOVERY_LED_H

#include "stm32l476xx.h"

void LED_Init(void);

void PB3_LED_Toggle(void);
void PA2_LED_Toggle(void);
void PB6_LED_Toggle(void);
void PB7_LED_Toggle(void);
void All_LED_Toggle(void);



#endif

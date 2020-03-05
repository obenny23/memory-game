/*
 * ECE 153B - Winter 2020
 *
 * Name(s): Benigno Ortega, Javier Jimenez
 * Section: T 7-9:50 
 */

#ifndef __STM32L476G_DISCOVERY_SYSTICK_H
#define __STM32L476G_DISCOVERY_SYSTICK_H

#include "stm32l476xx.h"

void SysTick_Init(void);
void SysTick_Handler(void);

void delay(uint32_t T);

#endif

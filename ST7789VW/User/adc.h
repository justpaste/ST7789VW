#ifndef __ADC11_H
#define __ADC11_H

#include "stm32f0xx.h"

void ADC_Config(void);
uint16_t Get_Adc(uint8_t ch);  
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times);


#endif

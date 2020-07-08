#ifndef MY_ADC_H_
#define MY_ADC_H_

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include "../gpio/Led.h"
#include "../uart/Uart.h"

void adc_init(void);

uint16_t adc_get_LM35(void);
uint16_t adc_get_Poti(void);

#endif /* MY_ADC_H_ */


#ifndef MY_ADC_H_
#define MY_ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void adc_init(void);

uint32_t adc_get_LM35(void);
uint32_t adc_get_Poti(void);

#endif /* MY_ADC_H_ */


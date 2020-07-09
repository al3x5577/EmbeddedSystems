#ifndef MY_ADC_H_
#define MY_ADC_H_

/**
 If DEBUG_LEDS_ADC is defined, Leds will visualise action:
 (init will also send a uart message if this flag is defined)
 
 LED3: ISR routine finished (is cleared at start of ISR and set at the end)
 LED4: LM35 ADCs are running
 LED5: Poti ADCs are running
 LED6: Init complete
 */
// #define DEBUG_LEDS_ADC

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include "../gpio/Led.h"
#include "../uart/Uart.h"

/**
 Initialises ADC with ISR
 ADC will always run in backround and trigger a new conversion after the last conversion is handled
 */
void adc_init(void);

/**
 Takes the last 8 values of the AD conversion and calculates the average.
 
 Returns:
 The average multiplied by 0.4883 to display Temperatur in Degree Celsius
 */
uint16_t adc_get_LM35(void);

/**
 Takes the last 8 values of the AD conversion and calculates the average.
 
 Returns:
 The average. Value between 0..1024
 */
uint16_t adc_get_Poti(void);

#endif /* MY_ADC_H_ */


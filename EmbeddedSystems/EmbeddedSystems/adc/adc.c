// PA0 = Temperatur
// PA1 = Poti

#include "adc.h"

// LM35-DZ Temperatur sensor data
uint16_t LM35_Array[8] = {0};
uint8_t index_LM35 = 42;

// Poti data
uint16_t Poti_Array[8] = {0};
uint8_t index_Poti = 42;


void adc_init() {
    // Set prescaler to 128
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    
    // Set ADC enable, start conversion, set ADC interrupt
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADIE);
    
#ifdef DEBUG_LEDS_ADC
    uart_send_isr("ADC init complete\n");
    Led6_On();
#endif
}

uint16_t adc_get_LM35() {
    
    uint32_t avg = 0;
    
    for (int i = 0; i < 8; i++) {
        avg += LM35_Array[i];
    }
    avg = avg / 8;
    
    avg = (int) avg * 0.4883;   // convert to mV, divide by factor of LM35-DZ
    
    return (avg & 0xffff);  // Return a 16 bit value
}

uint16_t adc_get_Poti() {
    
    uint32_t avg = 0;
    
    for (int i = 0; i < 8; i++) {
        avg += Poti_Array[i];
    }
    
    avg = avg / 8;
    
    return (avg & 0xffff);  // Return a 16 bit value
}

ISR(ADC_vect){
    volatile uint16_t res = ADC;
#ifdef DEBUG_LEDS_ADC
    Led3_Off();
#endif
    
    switch (ADMUX & (1 << MUX0)) {
        case 0:
            if (index_LM35 == 42) { // Trash first conversion
                index_LM35 = 0;
#ifdef DEBUG_LEDS_ADC
                Led4_On();
#endif
            }else if (index_LM35 >= 0 && index_LM35 <= 7) {
                LM35_Array[index_LM35] = res;
                index_LM35++;
            }else {
                ADMUX &= ~(30); // Set MUX1..4 to 0
                ADMUX |= (1 << MUX0);
                index_LM35 = 42;
#ifdef DEBUG_LEDS_ADC
                Led4_Off();
#endif
            }
            break;
            
        case 1:
            if (index_Poti == 42) { // Trash first conversion
#ifdef DEBUG_LEDS_ADC
                Led5_On();
#endif
                index_Poti = 0;
            }else if (index_Poti >= 0 && index_Poti <= 7) {
                Poti_Array[index_Poti] = res;
                index_Poti++;
            }else {
                ADMUX &= ~(31); // Set MUX0..4 to 0
                index_Poti = 42;
#ifdef DEBUG_LEDS_ADC
                Led5_Off();
#endif
            }
            break;
            
        default:
            break;
    }
#ifdef DEBUG_LEDS_ADC
    Led3_On();
#endif
    ADCSRA |= (1 << ADSC) | (1 << ADIE);
}

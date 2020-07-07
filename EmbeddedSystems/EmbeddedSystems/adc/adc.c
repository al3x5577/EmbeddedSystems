// PA0 = Temperatur
// PA1 = Poti

#include "adc.h"

enum adc_select {
    Temperatur = 0,
    Poti = 1
} pin = 0;

uint16_t LM35_Array[8] = {0};
uint8_t index_LM35 = 0;
uint16_t Poti_Array[8] = {0};
uint8_t index_Poti = 0;

void adc_init() {
    ADMUX = 0;  // AREF, Right Adjust, ADC0
    
    ADCSRB = 3; // Set trigger to Timer0 Compare Match
    
    ADCSRA = 7; // Set prescaler to 128
    ADCSRA |= (1 << ADEN) | (1 << ADSC); // Set ADC enable, no Auto trigger | (1 << ADATE)
    
    while (ADCSRA & (1 << ADSC));   // wait till first conversion is finished
    uint16_t trash = ADC;
    
    ADCSRA |= (1 << ADIE) | (1 << ADSC); // ADC interrupt
}

uint32_t adc_get_LM35() {
    if (LM35_Array[7] == 0) {
        return 0; // Not enoght data in Array
    }
    
    uint32_t avg = 0;
    
    for (int i = 0; i < 8; i++) {
        avg += LM35_Array[i];
    }
    avg = avg / 8;
    
    return avg;
}

uint32_t adc_get_Poti() {
    if (Poti_Array[7] == 0) {
        return 0; // Not enoght data in Array
    }
    
    uint32_t avg = 0;
    
    for (int i = 0; i < 8; i++) {
        ADCSRA &= (1 << ADIE);
        avg += Poti_Array[i];
        ADCSRA |= (1 << ADIE);
    }
    avg = avg / 8;
    
    return avg;
}

ISR(ADC_vect){
    volatile uint16_t res = ADC;
    switch (ADMUX) {
        case 1:
			Led7_On();
            if (index_LM35 >= 8 || index_LM35 == 0) {
                LM35_Array[0] = res;
                index_LM35 = 1;
            }else {
                LM35_Array[index_LM35] = res;
                index_LM35++;
            }
            pin = Poti;
            ADMUX = 2;
            break;
            
        case 2:
			Led8_On();
            if (index_Poti >= 8 || index_Poti == 0) {
                Poti_Array[0] = res;
                index_Poti = 1;
            }else {
                Poti_Array[index_Poti] = res;
                index_Poti++;
            }
            pin = Temperatur;
            ADMUX = 1;
            break;
            
        default:
            break;
    }
    
    ADCSRA |= (1 << ADSC);
}

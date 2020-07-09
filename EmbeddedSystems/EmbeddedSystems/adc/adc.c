// PA0 = Temperatur
// PA1 = Poti

#include "adc.h"

volatile uint16_t LM35_Array[8] = {0};
volatile uint8_t index_LM35 = 42;
volatile uint16_t Poti_Array[8] = {0};
volatile uint8_t index_Poti = 42;

volatile uint16_t temp_index1 = 0;

void adc_init() {
    // ADMUX = 0x00;  // AREF, Right Adjust, ADC0
    
    // ADCSRB = 0; // Set trigger to free running mode
    
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // Set prescaler to 128
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADIE); // Set ADC enable, start conversion, set auto-trigger, set ADC interrupt
    
    ADMUX |= (1 << MUX0);
    
    uart_send_isr("ADC init complete\n");
    Led6_On();
}

uint16_t adc_get_LM35() {
    
    uint32_t avg = 0;
    
    for (int i = 0; i < 8; i++) {
        ADCSRA &= ~(1 << ADIE);
        avg += Poti_Array[i];
        ADCSRA |= (1 << ADIE);
    }
    avg = avg / 8;
    
    return (avg & 0xffff);  // Return a 16 bit value
}

uint16_t adc_get_Poti() {
    
    uint32_t avg = 0;
    
    for (int i = 0; i < 8; i++) {
        ADCSRA &= ~(1 << ADIE);
        avg += Poti_Array[i];
        ADCSRA |= (1 << ADIE);
    }
    
    char str2[20];
    sprintf(str2, "AVG: %d\n", avg);
    uart_send_isr(str2);
    
    avg = avg / 8;
    
    sprintf(str2, "AVG/8: %d\n", avg);
    uart_send_isr(str2);
    
    return (avg & 0xffff);  // Return a 16 bit value
}

ISR(ADC_vect){
    volatile uint16_t res = ADC;
    Led3_Off();
    
    char str2[10];
    sprintf(str2, "Res: %d\n", res);
    //uart_send_isr(str2);
    
    if ( temp_index1 == 0){
        Led7_On();
        Led8_Off();
        temp_index1 = 1;
    }else  {
        Led7_Off();
        Led8_On();
        temp_index1 = 0;
    }
    
    if (index_Poti == 42) { // Trash first conversion
        Led5_On();
        index_Poti = 0;
    }else if (index_Poti >= 0 && index_Poti <= 7) {
        Poti_Array[index_Poti] = res;
        index_Poti++;
    }else {
        index_Poti = 42;
        Led5_Off();
    }
    
    /*switch (ADMUX & (1 << MUX0)) {
        case 0:
			//Led7_On();
            if (index_LM35 == 42) { // Trash first conversion
                index_LM35 = 0;
                Led4_On();
            }else if (index_LM35 >= 0 && index_LM35 <= 7) {
                LM35_Array[index_LM35] = res;
                index_LM35++;
            }else {
                ADMUX &= ~(30); // Set MUX1..4 to 0
                ADMUX |= (1 << MUX0);
                index_LM35 = 42;
                Led4_Off();
            }
            break;
            
        case 1:
            //Led8_On();
            if (index_Poti == 42) { // Trash first conversion
                Led5_On();
                index_Poti = 0;
            }else if (index_Poti >= 0 && index_Poti <= 7) {
                Poti_Array[index_Poti] = res;
                index_Poti++;
            }else {
                ADMUX &= ~(31); // Set MUX0..4 to 0
                index_Poti = 42;
                Led5_Off();
            }
            break;
            
        default:
            break;
    }*/
    
    Led3_On();
    ADCSRA |= (1 << ADSC) | (1 << ADIE);
}

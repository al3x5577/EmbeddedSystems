// PA0 = Temperatur
// PA1 = Poti

#include "adc.h"

uint16_t LM35_Array[8] = {0};
uint8_t index_LM35 = 42;
uint16_t Poti_Array[8] = {0};
uint8_t index_Poti = 42;

uint8_t temp_index = 0;

void adc_init() {
    // ADMUX = 0x00;  // AREF, Right Adjust, ADC0
    
    // ADCSRB = 3; // Set trigger to Timer0 Compare Match
    
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // Set prescaler to 128
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADIE); // Set ADC enable, start conversion, set ADC interrupt
    
    uart_send_isr("ADC init complete\n");
    Led6_On();
}

uint16_t adc_get_LM35() {
    if (LM35_Array[7] == 0) {
        return 0; // Not enoght data in Array
    }
    
    uint32_t avg = 0;
    
    for (int i = 0; i < 8; i++) {
        avg += LM35_Array[i];
    }
    avg = avg / 8;
    
    return (avg & 0xffff);  // Return a 16 bit value
}

uint16_t adc_get_Poti() {
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
    
    return (avg & 0xffff);  // Return a 16 bit value
}

ISR(ADC_vect){
	Led2_Off();
    uint16_t res = ADC;
    
    /*uint8_t uart_success = 1;
    if (uart_success) {
        char str[20];
        sprintf(str, "Res: %d\n", res);
        if (uart_send_isr(str) > 0){
            uart_success = 0;
            temp_index++;
        }
    }else {
        temp_index++;
        if (temp_index >= 100) {
            temp_index = 0;
            uart_success = 1;
        }
    }*/
    char str[20];
    sprintf(str, "Res: %d\n", res);
    uart_send_isr(str);
    
    switch (ADMUX & (1 << MUX0)) {
        case 0:
			Led7_On();
            if (index_LM35 == 42) {
                index_LM35 = 0; // Trash first conversion
                Led4_On();
            }else if (index_LM35 >= 0 && index_LM35 <= 7) {
                LM35_Array[index_LM35] = res;
                index_LM35++;
            }else {
                ADMUX |= (1 << MUX0);
                index_LM35 = 42;
                Led4_Off();
            }
            break;
            
        case 1:
            Led8_On();
            if (index_Poti == 42) {
                Led5_On();
                index_Poti = 0; // Trash first conversion
            }else if (index_Poti >= 0 && index_Poti <= 7) {
                Poti_Array[index_Poti] = res;
                index_Poti++;
            }else {
                ADMUX &= ~(1 << MUX0);
                index_Poti = 42;
                Led4_Off();
            }
            break;
            
        default:
            break;
    }
    
    // ADCSRA |= (1 << ADSC);   temporary moved lol
}

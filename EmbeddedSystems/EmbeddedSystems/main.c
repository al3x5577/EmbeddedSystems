/*
 * Projekt1.c
 *
 * Created: 26.05.2020 00:20:09
 * Author : MSR
 */ 

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "gpio/Taster.h"
#include "gpio/Led.h"
#include "playground/Playground.h"
#include "timer/Timer.h"
#include "stateMachine/TrafficLight.h"
#include "uart/Uart.h"
#include <avr/interrupt.h>
#include "adc/adc.h"

#define CLK_F_MHZ 16

uint8_t iahsdfoads = 0;
uint16_t afdsfasdf = 0;

void Timer2Test() {
    if (afdsfasdf == 500) {
        if ( iahsdfoads == 0){
            Led4_On();
            Led5_Off();
            iahsdfoads = 1;
        }else  {
            Led4_Off();
            Led5_On();
            iahsdfoads = 0;
        }
        afdsfasdf = 0;
    }else {
        afdsfasdf++;
    }
}

int main(void) {
	
    cli();
    Led_init(0);	// Don't set LEDs at PORTD
	Taster_init();
    Timer_init(CLK_F_MHZ); // Init timer with 16MHZ clock
    Timer2_init(CLK_F_MHZ, Timer2Test); // Init timer with 16MHZ clock
	uart_init_isr();
    adc_init();
	sei();
    
    uint16_t timeVarMain = Timer_getTick();
    char data_s;
    char data[50] = {0};
    int isafd = 0;
	char str[65];
    uint16_t Poti = 0;
	
    while (1) {
        
        if((Timer_getTick() - timeVarMain) >= 500){
            timeVarMain = Timer_getTick();
            
            if ( isafd == 0){
                Led1_On();
                Led2_Off();
                isafd = 1;
            }else  {
                Led1_Off();
                Led2_On();
                isafd = 0;
            }
            
            uint16_t LM35 = adc_get_LM35();
            Poti = adc_get_Poti();
            
            
            cli();
            sprintf(str, "Temp: %d\n", LM35);
            uart_send_isr(str);
            sprintf(str, "Poti: %d\n", Poti);
            uart_send_isr(str);
            sei();
            
            
        }
        
        
        /*while ((data_s = uart_get_data()) && i <= 48) {
            data[i] = data_s;
            i++;
        }
        data[i+1] = '\0';
        
        
        if (i > 0) {
			
            switch (data[0]) {
                case '1':
                    if (data[1] == '1') {
                        Led1_On();
                        uart_send_isr("Led1 On\n");
                    }else if (data[1] == '0') {
                        Led1_Off();
                        uart_send_isr("Led1 Off\n");
                    }
                    break;
                    
                case '2':
                    if (data[1] == '1') {
                        Led2_On();
                        uart_send_isr("Led2 On\n");
                    }else {
                        Led2_Off();
                        uart_send_isr("Led2 Off\n");
                    }
                    break;
                    
                case '3':
                    if (data[1] == '1') {
                        Led3_On();
                        uart_send_isr("Led3 On\n");
                    }else {
                        Led3_Off();
                        uart_send_isr("Led3 Off\n");
                    }
                    break;
                    
                case '4':
                    if (data[1] == '1') {
                        Led4_On();
                        uart_send_isr("Led4 On\n");
                    }else {
                        Led4_Off();
                        uart_send_isr("Led4 Off\n");
                    }
                    break;
                    
                default:
                    
                    sprintf(str, "Received: %s\n", data);
                    uart_send_isr(str);
                    break;
            }
        }
        i = 0;*/
		
        /*
         // UART Echo
         while ((data_s = uart_get_data()) && i <= 48) {
            data[i] = data_s;
            i++;
        }
        data[i+1] = '\0';
        
        if (i > 0) {
            char str[65];
            
            sprintf(str, "Received: %s\n", data);
            
            uart_send_isr(str);
        }
        
        i = 0;*/
        
        /*
         // Speed test of UART
         if((Timer_getTick() - timeVarMain) >= 100){
            timeVarMain = Timer_getTick();
            
            if (uart_send_isr("Hallo Welt!\n") == 0 && uart_send_isr("Kannst du mich hoeren?\n") == 0 && uart_send_isr("Das sieht sehr gut aus!!!!\n") == 0 ) {
                Led6_On();
                Led1_Off();
            }else {
                Led6_Off();
                Led1_On();
            }
        }*/
        
        //trafficLight(0);
        //playground();
    }
}



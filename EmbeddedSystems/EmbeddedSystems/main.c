/*
 * Projekt1.c
 *
 * Created: 26.05.2020 00:20:09
 * Author : MSR
 */ 

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

#include "gpio/Taster.h"
#include "gpio/Led.h"
#include "playground/Playground.h"
#include "timer/Timer.h"
#include "stateMachine/TrafficLight.h"
#include "uart/Uart.h"
#include <avr/interrupt.h>

#define CLK_F_MHZ 16

int main(void) {
	
    cli();
    Led_init(0);	// Don't set LEDs at PORTD
	Taster_init();
    Timer_init(CLK_F_MHZ); // Init timer with 16MHZ clock
	uart_init_isr();
	sei();
    
    uint16_t timeVarMain = 0;
    while (1) {
        
        if((Timer_getTick() - timeVarMain) >= 100){
            timeVarMain = Timer_getTick();
            
            if (uart_send_isr("Hallo Welt!\n") == 0 && uart_send_isr("Kannst du mich hoeren?\n") == 0 && uart_send_isr("Das sieht sehr gut aus!!!!\n") == 0 ) {
                Led6_On();
                Led1_Off();
            }else {
                Led6_Off();
                Led1_On();
            }
        }
        
        //trafficLight(0);
        //playground();
    }
}



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
#define MY_BAUD_UART 9600

int main(void) {
	
    cli();
    Led_init(0);	// Don't set LEDs at PORTD
	Taster_init();
    Timer_init(CLK_F_MHZ); // Init timer with 16MHZ clock
	uart_init(MY_BAUD_UART);
	sei();
	
    uint8_t state_testBoard = 0;
    uint16_t last_time = 0;
	uint8_t  toggle_asdf = 1;
    
    /**
    Toggle PORTB every 500ms -> LEDs blink with 1 Hz, accuracy: +- 70 us
    (There could be a lag if timer_count was cleared, approximately every 65,5 seconds)
    */
    uint8_t aksfjbalsdkjb = 0;
	
    while (1) {
		
		/*if (Taster2_get()) {
			toggle_asdf = !toggle_asdf;
		}
		
		if (toggle_asdf) {
			// Check if time difference is more than 500 ms
			if ( (Timer_getTick() - last_time) >= 500 ) {
				last_time = Timer_getTick();
				
				// toggle leds
				if (state_testBoard) {
					state_testBoard = 0;
					PORTB = 0x00;
					}else {
					state_testBoard = 1;
					PORTB = 0xFF;
				}
			}
		}else {
			PORTB = 0x00;
		}*/
        
        if (aksfjbalsdkjb == 0) {
            if ( (Timer_getTick() - last_time) >= 500 ) {
                last_time = Timer_getTick();
                
                if(uart_send("Hallo Welt!!") == -1) {
                    Led1_On();
                }
                
                while ( !(UCSR0A & (1 << TXC0)) )
                    ;
                
                Led7_On();
                Led8_On();
                aksfjbalsdkjb = 1;
            }
        }else {
            if ( (Timer_getTick() - last_time) >= 200 ) {
                last_time = Timer_getTick();
                Led7_Off();
                Led8_Off();
                aksfjbalsdkjb = 0;
            }
        }
        
        
        
        //trafficLight(0);
        //playground();
    }
}



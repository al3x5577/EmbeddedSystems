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


int main(void) {
	
    Taster_init();
    Led_init();
	
    while (1) {
        if (Taster1_get()) {
            Led1_On();
        }else {
			Led1_Off();
		}
        if (Taster2_get()) {
	        Led2_On();
	    }else {
	        Led2_Off();
        }
        if (Taster3_get()) {
	        Led3_On();
	        }else {
	        Led3_Off();
        }
		if (Taster4_get()) {
			Led4_On();
			}else {
			Led4_Off();
		}
    }
    
    void uebung1() {
        DDRB = 0xFF;
        PORTB = 0xAC;
        
        //
        // Uebung
        //
        
        // Bit 1 in Register PORTB setzten
        PORTB |= (1 << 1);
        
        // Bit 3 in Register PORTB setzten
        PORTB |= (1 << 3);
        
        // Bit 5 in Register PORTB setzten
        PORTB |= (1 << 5);
        
        // Bit 2 in Register PORTB löschen
        PORTB &= ~(1 << 2);
        
        // Bit 4 in Register PORTB löschen
        PORTB &= ~(1 << 4);
        
        // Bit 6 in Register PORTB löschen
        PORTB &= ~(1 << 6);
        
        // Bit 7 in Register PORTB invertieren
        PORTB ^= (1 << 7);
        
        // Bit 2 in Register PORTB invertieren
        PORTB ^= (1 << 2);
        
        PORTB = 0xFF;
        
        // Bit 4 in Register PINB abfragen, ob gesetzt
        if ( (PORTB & (1 << 4)) != 0) {
            // Bit ist gesetzt
            PORTB = 0x00;
        }
        
        // Bit 6 in Register PINB abfragen, ob clear
        if ( (PORTB & (1 << 6)) == 0) {
            // Bit ist clear
            PORTB = 0xFF;
        }
    }
}


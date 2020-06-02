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


int main(void) {
	
    Led_init();
	Taster_init();
    Timer_init();
	
	volatile int x = 0;
	
    while (1) {
        //playground();
		x++;
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


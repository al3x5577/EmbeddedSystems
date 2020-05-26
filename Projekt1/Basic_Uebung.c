#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

int main(void) {
    
    DDRB = 0xFF;
    PORTB = 0xAB;
    
    //
    // Uebung lol
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
    
    // Bit 4 in Register PINB abfragen, ob gesetzt
    if ( (PORTB & (1 << 4)) == 1) {
        // Bit ist gesetzt
    }
    
    // Bit 6 in Register PINB abfragen, ob clear
    if ( (PORTB & (1 << 6)) == 0) {
        // Bit ist clear
    }
    
    while (1){
        // Do some stuff
        PORTB = 0xFF;
        _delay_ms (500);
        PORTB = 0x00;
        _delay_ms (500);
    }
}

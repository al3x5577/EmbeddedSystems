
#include "Taster.h"

// If logic is set wrong, change these
#define TASTER_RETURN_VALUE_LOW 1
#define TASTER_RETURN_VALUE_HIGH 0


/**
 Set GPIOs to input for switches t:
 ---------------------
 t1 - ioD7
 t2 - ioD6
 t3 - ioD5
 t4 - ioC2
 ---------------------
 - DDR Reg has to be set to 0
 - PORT Reg has to be set to 1
 -> Pin is input with pull-up
 */
void Taster_init() {
    // set to inputs
    DDRC &= ~(1 << 2);
    DDRD &= ~( (1 << 7) | (1 << 6) | (1 << 5) );
    
    // enable pull-up
    PORTC |= (1 << 2);
    PORTD |= (1 << 7) | (1 << 6) | (1 << 5);
}

/**
 Taster1 - ioD7
 */
uint8_t Taster1_get(void) {
    int state = PIND;
    if ( (state & (1<<7)) == 0 ) {
        return TASTER_RETURN_VALUE_LOW;
    } else {
        return TASTER_RETURN_VALUE_HIGH;
    }
}

/**
Taster2 - ioD6
*/
uint8_t Taster2_get(void) {
    uint8_t state = PIND;
    if ( (state & (1<<6)) == 0 ) {
        return TASTER_RETURN_VALUE_LOW;
    } else {
        return TASTER_RETURN_VALUE_HIGH;
    }
}

/**
Taster3 - ioD5
*/
uint8_t Taster3_get(void) {
    uint8_t state = PIND;
    if ( (state & (1<<5)) == 0 ) {
        return TASTER_RETURN_VALUE_LOW;
    } else {
        return TASTER_RETURN_VALUE_HIGH;
    }
}

/**
Taster4 - ioC2
*/
uint8_t Taster4_get(void) {
    uint8_t state = PINC;
    if ( (state & (1<<2)) == 0 ) {
        return TASTER_RETURN_VALUE_LOW;
    } else {
        return TASTER_RETURN_VALUE_HIGH;
    }
}

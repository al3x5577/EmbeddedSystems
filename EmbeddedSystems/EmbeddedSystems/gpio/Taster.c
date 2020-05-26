
// If pullup - pulldown is set wrong, change these
#define RETURN_VALUE_LOW 1
#define RETURN_VALUE_HIGH 0

/**
 Set GPIOs to input for switches t:
 t1 - ioD7
 t2 - ioD6
 t3 - ioD5
 t4 - ioC2
 */
void Taster_init() {
    DDRC |= (1 << 2);
    DDRD |= (1 << 7) | (1 << 6) | (1 << 5);
}

/**
 Taster1 - ioD7
 */
uint8_t Taster1_get(void) {
    uint8_t state = PIND;
    if ( (state & (1<<7)) == 0 ) {
        return RETURN_VALUE_LOW;
    } else {
        return RETURN_VALUE_HIGH;
    }
}

/**
Taster1 - ioD6
*/
uint8_t Taster2_get(void) {
    uint8_t state = PIND;
    if ( (state & (1<<6)) == 0 ) {
        return RETURN_VALUE_LOW;
    } else {
        return RETURN_VALUE_HIGH;
    }
}

/**
Taster1 - ioD5
*/
uint8_t Taster3_get(void) {
    uint8_t state = PIND;
    if ( (state & (1<<5)) == 0 ) {
        return RETURN_VALUE_LOW;
    } else {
        return RETURN_VALUE_HIGH;
    }
}

/**
Taster1 - ioC2
*/
uint8_t Taster4_get(void) {
    uint8_t state = PINC;
    if ( (state & (1<<2)) == 0 ) {
        return RETURN_VALUE_LOW;
    } else {
        return RETURN_VALUE_HIGH;
    }
}

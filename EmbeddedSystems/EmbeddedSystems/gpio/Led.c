
#include <Led.h>

void Led_init(void) {
    // Set PORTB to outputs
    DDRB = 0xFF;
}


/**
 led1 - ioB7
 */
void Led1_On(void) {
    PORTB |= (1 << 7);
}
void Led1_Off(void) {
    PORTB &= ~(1 << 7);
}

/**
led2 - ioB6
*/
void Led2_On(void) {
    PORTB |= (1 << 6);
}
void Led2_Off(void) {
    PORTB &= ~(1 << 6);
}

/**
led3 - ioB5
*/
void Led3_On(void) {
    PORTB |= (1 << 5);
}
void Led3_Off(void) {
    PORTB &= ~(1 << 5);
}

/**
led4 - ioB4
*/
void Led4_On(void) {
    PORTB |= (1 << 4);
}
void Led4_Off(void) {
    PORTB &= ~(1 << 4);
}

/**
led5 - ioB3
*/
void Led5_On(void) {
    PORTB |= (1 << 3);
}
void Led5_Off(void) {
    PORTB &= ~(1 << 3);
}

/**
led6 - ioB2
*/
void Led6_On(void) {
    PORTB |= (1 << 2);
}
void Led6_Off(void) {
    PORTB &= ~(1 << 2);
}

/**
led7 - ioB1
*/
void Led7_On(void) {
    PORTB |= (1 << 1);
}
void Led7_Off(void) {
    PORTB &= ~(1 << 1);
}

/**
led8 - ioB0
*/
void Led8_On(void) {
    PORTB |= (1 << 0);
}
void Led8_Off(void) {
    PORTB &= ~(1 << 0);
}

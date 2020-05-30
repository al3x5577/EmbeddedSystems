#ifndef PLAYGROUND_H_
#define PLAYGROUND_H_

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 1000000
#endif
#include <util/delay.h>

/**
 (pseude main function)
 
 modes:
 - button1 pressed -> testTasterLed()
 - button2 pressed -> testBoard()
 - button3 pressed -> lauflicht()
 - button4 pressed -> increment()
*/
void playground(void);


/**
 Starting at Led0, the Led next to the current led will turn on at the same time the current led turns off.
 If last led is reached, the direction will change.
 
 Only one led is active at once
*/
void lauflicht(void);

/**
 Increment if button 1 is pressed, decrement if button 2 is pressed.
 Value of count will display with leds. if count is dez 5, 5 leds will turn on
*/
void increment(void);

/**
 Switches PORTB on and off with a delay off 500 ms
*/
void testBoard(void);

/**
 If button1 is pressed, led1 will turn on. If button2 is pressed, led2 will turn on and so on...
*/
void testTasterLed(void);

#endif /* PLAYGROUND_H_ */

#ifndef PLAYGROUND_H_
#define PLAYGROUND_H_

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 1000000
#endif
#include <util/delay.h>

/**
modes:
- button1 pressed -> testTasterLed()
- button2 pressed -> testBoard()
- button3 pressed -> lauflicht()
- button4 pressed -> increment()
*/
void playground(void);


void lauflicht(void);

/**
 Increment if button 1 is pressed, decrement if button 2 is pressed
 */
void increment(void);

void testBoard(void);

void testTasterLed(void);

#endif /* PLAYGROUND_H_ */

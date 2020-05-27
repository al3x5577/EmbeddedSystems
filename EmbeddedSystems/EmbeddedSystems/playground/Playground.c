
#include "Playground.h"


/**
modes:
- button1 pressed -> testTasterLed()
- button2 pressed -> testBoard()
- button3 pressed -> lauflicht()
- button4 pressed -> increment()
*/
void playground() {
    static int mode = 0;
    
    if (mode == 0) {    // mode selection
        
        // test buttons
        if (Taster1_get()) {
            mode = 1;
        } else if (Taster2_get()) {
            mode = 2;
        } else if (Taster3_get()) {
            mode = 3;
        } else if (Taster4_get()) {
            mode = 4;
        }
        
    } else {    // run
        
        // reset if button 1 and button 2 are pressed
        if (Taster1_get() && Taster2_get()) {
            mode = 0;
        }
        
        // execute
        switch (mode) {
            case 1:
                testTasterLed();
                break;
            case 2:
                testBoard();
                break;
            case 3:
                lauflicht();
            case 4:
                increment();
                break;
            default:
                mode = 0;
                break;
        }
    }
}

void lauflicht() {
    // TODO
}

/**
 Increment if button 1 is pressed, decrement if button 2 is pressed
 */
void increment() {
    static int count = 0;
    if (Taster1_get()) {
        count++;
    }else if (Taster2_get()) {
        if (count > 0) {
            count--;
        }
    }
    
    uint8_t ledByte = 0;
    for (int i = 0; i < count; i++) {
        ledByte = ledByte << 1;
        ledByte++;
    }
    PORTB = ledByte;
}

void testBoard() {
    static bool state_testBoard = false;
    if (state_testBoard) {
        PORTB = 0x00;
        _delay_ms(500);
    }else {
        PORTB = 0xFF;
        _delay_ms(500);
    }
}

void testTasterLed() {
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

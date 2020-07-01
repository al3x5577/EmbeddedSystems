
#include "Playground.h"

uint16_t timeVarP = 0;

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
        Led1_On();
        Led4_On();
        Led5_On();
        Led8_On();
        
        // test buttons
        if (Taster1_get()) {
            mode = 1;
            PORTB = 0x00;
            Led1_On();
            _delay_ms(500);
            Led1_Off();
            timeVarP = Timer_getTick();
        } else if (Taster2_get()) {
            mode = 2;
            PORTB = 0x00;
            Led2_On();
            _delay_ms(500);
            Led2_Off();
            timeVarP = Timer_getTick();
        } else if (Taster3_get()) {
            mode = 3;
            PORTB = 0x00;
            Led3_On();
            _delay_ms(500);
            Led3_Off();
            timeVarP = Timer_getTick();
        } else if (Taster4_get()) {
            mode = 4;
            PORTB = 0x00;
            Led4_On();
            _delay_ms(500);
            Led4_Off();
            timeVarP = Timer_getTick();
        }
        
    } else {    // run
        
        // reset if button 1 and button 2 are pressed
        if (Taster1_get() && Taster2_get()) {
            mode = 0;
            _delay_ms(1000);
            PORTB = 0xFF;
            _delay_ms(500);
            PORTB = 0x00;
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
				break;
            case 4:
                increment();
                break;
            default:
                mode = 0;
                break;
        }
    }
}

/**
 Starting at Led0, the Led next to the current led will turn on at the same time the current led turns off.
 If last led is reached, the direction will change
 
 Only one led is active at once
 */
void lauflicht() {
    
    if((Timer_getTick() - timeVarP) >= 1000){
        timeVarP = Timer_getTick();
        
        
        static int laufCount = 0;
        static int direction = 0;   // 0=right, 1=left
        
        if (direction) {    // left
            if (laufCount <= 1) {
                direction = 0;
                laufCount++;
            } else {
                laufCount--;
            }
        }else { // right
            if (laufCount >= 8) {
                direction = 1;
                laufCount--;
            } else {
                laufCount++;
            }
        }
        
        // create byte
        int ledByte = 1;
        ledByte = ledByte << (laufCount - 1);
        
        // set Port
        PORTB = ledByte;
    }
}

/**
 Increment if button 1 is pressed, decrement if button 2 is pressed.
 Value of count will display with leds. if count is dez 5, 5 leds will turn on
 */
void increment() {
    static int count = 0;
    static int lockt1 = 0, lockt2 = 0;
    
    // If button is pressed and lock is released
    if (!lockt1 && Taster1_get()) {
        //count to max 8
        if (count <= 8) {
            count++;
        }
        // lock
        lockt1 = 1;
    }else if (!lockt2 && Taster2_get()) {
        //count to min 0
        if (count > 0) {
            count--;
        }
        // lock
        lockt2 = 1;
    }
    
    // if button is released, release lock
    if (!Taster1_get()) {
        lockt1 = 0;
    }
    if (!Taster2_get()) {
        lockt2 = 0;
    }
    
    // shift as many ones as count to byte
    int ledByte = 0;
    for (int i = 0; i < count; i++) {
        ledByte = ledByte << 1;
        ledByte++;
    }
    // set Port
    PORTB = ledByte;
}

/**
 Switches PORTB on and off with a delay off 500 ms
 */
void testBoard() {
    static int state_testBoard = 0;
    
    if((Timer_getTick() - timeVarP) >= 500){
        timeVarP = Timer_getTick();
        
        if (state_testBoard) {
            state_testBoard = 0;
            PORTB = 0x00;
        }else {
            state_testBoard = 1;
            PORTB = 0xFF;
        }
    }
}

/**
 If button1 is pressed, led1 will turn on. If button2 is pressed, led2 will turn on and so on...
 */
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

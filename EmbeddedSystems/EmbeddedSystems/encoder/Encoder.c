
#include "Encoder.h"

volatile uint8_t enc_state = 0;
volatile uint8_t st_m_state = 0;
volatile uint8_t last = 0;
volatile uint8_t new = 0;

volatile int16_t val = 0;

volatile uint16_t asdjna = 0;

/**
 State machine for encoder
 */
void encoder_process() {
    
    if (asdjna >= 500) {
        PORTB ^= 0xff;
        asdjna = 0;
    }else {
        asdjna++;
    }
    
    switch (st_m_state) {
        case 1: // Init state
            
            if (enc_state == 1) {
                // Rotation forward
                st_m_state = 2;
                
            } else if (enc_state == 2) {
                // Rotation backward
                st_m_state = 5;
            }
            break;
            
        case 2: // Rotation forward
            
            if (enc_state == 3) {
                // Still rotating forward
                st_m_state = 3;
                
            } else if (enc_state == 0) {
                // Fail, go back to init state (maybe bouncing)
                st_m_state = 1;
            }
            break;
            
        case 3: // Rotation forward
        
            if (enc_state == 2) {
                // Still rotating forward
                st_m_state = 4;
                
            } else if (enc_state == 1) {
                // Fail, go back to previous state (maybe bouncing)
                st_m_state = 2;
            }
            break;
            
        case 4: // Rotation forward
        
            if (enc_state == 0) {
                // Forward Rotation done
                st_m_state = 1;
                val++;
                
            } else if (enc_state == 3) {
                // Fail, go back to previous state (maybe bouncing)
                st_m_state = 3;
            }
            break;
            
            
        case 5: // Rotation backward
        
            if (enc_state == 0) {
                // Fail, go back to init state (maybe bouncing)
                st_m_state = 1;
                
            } else if (enc_state == 3) {
                // Still rotating backward
                st_m_state = 6;
            }
            break;
            
        case 6: // Rotation backward
        
            if (enc_state == 2) {
                // Fail, go back to previous state (maybe bouncing)
                st_m_state = 5;
                
            } else if (enc_state == 1) {
                // Still rotating backward
                st_m_state = 7;
            }
            break;
            
        case 7: // Rotation backward
        
            if (enc_state == 3) {
                // Fail, go back to previous state (maybe bouncing)
                st_m_state = 6;
                
            } else if (enc_state == 0) {
                // Rotating backward done
                st_m_state = 1;
                val--;
            }
            break;

            
        default:
            st_m_state = 1;
            break;
    }
}


void encoder_isr(){
    
    // Update enc_state
    enc_state = (PINC & ( (1 << PC6) | (1 << PC7) )) >> 6;
    
    new = enc_state;
    
    
    // If nothing changed, keep state
    if (last == new) {
        return;
    }
    
    // State machine
    encoder_process();
    
    last = new;
}

void encoder_init( void ){
    
    // Init state machine
    st_m_state = 1;
    
    // Init timer (16MHZ, call encoder_isr() at timer isr)
    Timer2_init(16, encoder_isr);
}

int16_t encoder_get(){
    TIMSK2 &= ~(1 << OCIE0A);
    int16_t temp = val;
    TIMSK2 |= (1 << OCIE0A);
    return temp;
}

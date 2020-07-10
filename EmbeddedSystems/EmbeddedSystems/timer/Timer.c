
#include "Timer.h"

typedef struct TIMER_REG{
    // TCCR0A
    uint8_t mode00 :1;
    uint8_t mode01 :1;
    uint8_t res :2;
    uint8_t COM :4;
    
    // TCCR0B
    uint8_t prescaler :3;
    uint8_t mode02 :1;
    uint8_t res2 :2;
    uint8_t FOC :2;
    
    // TCNT0
    uint8_t timerVar :8;
    
    // OCR0A
    uint8_t compareValueA :8;
    
    // OCR0B
    uint8_t compareValueB :8;
    
}TIMER_REG_t;

volatile uint16_t timer_count = 0;

void Timer_init(uint8_t clockFreqMhz) {
    Timer_init_withoutStruct(clockFreqMhz);
}

void Timer_init_withStruct(uint8_t clockFreqMhz) {
    TIMER_REG_t *TIMER0 = (TIMER_REG_t*)(0x44);
    
    // datasheet page 97
    // set mode to clear timer on compare (CTC)
    TIMER0->mode02 = 0;
    TIMER0->mode01 = 1;
    TIMER0->mode00 = 0;
    
    switch (clockFreqMhz) {
        case 16:
            // extern osc (16 MHZ)
            TIMER0->compareValueA = 249;   // dez 249; range 0 - 249 -> 250 cycles till interrupt
            TIMER0->compareValueB = 124;   // dez 124; range 0 - 124 -> 125 cycles till interrupt
            TIMER0->prescaler = 3;  // set prescaler to 1/64
            break;
            
        default:
            // inter osc (8 MHZ divided by 8 -> 1 MHZ clock)
            TIMER0->compareValueA = 0x7C;   // dez 124; range 0 - 124 -> 125 cycles till interrupt
            TIMER0->compareValueB = 63;   // dez 61; range 0 - 61 -> 62 cycles till interrupt
            TIMER0->prescaler = 2;  // set prescaler to 1/8
            break;
    }
    
    TIMSK0 |= (1 << OCIE0B);   // enable Output Compare Match B Interrupt
    TIMSK0 |= (1 << OCIE0A);    // enable Output Compare Match A Interrupt
    TIMSK0 &= ~(1 << TOIE0);    // disable timer overflow interrupt
}

void Timer_init_withoutStruct(uint8_t clockFreqMhz) {
    // datasheet page 97
    // set mode to clear timer on compare (CTC)
    TCCR0B &= ~(1 << WGM02);
    TCCR0A |= (1 << WGM01);
    TCCR0A &= ~(1 << WGM00);
    
    
    switch (clockFreqMhz) {
        case 16:
            // extern osc (16 MHZ)
            
            // set OCR0A-reg (top value of timer)
            OCR0A = 249;   // dez 249; range 0 - 249 -> 250 cycles till interrupt
            
            // set OCR0B-reg (top value B of timer)
            OCR0B = 34;   // dez 124; range 0 - 124 -> 125 cycles till interrupt
            
            // set prescaler to 1/64
            TCCR0B &= ~(1 << CS02);
            TCCR0B |= (1 << CS01);
            TCCR0B |= (1 << CS00);
            break;
            
        default:
            // inter osc (8 MHZ divided by 8 -> 1 MHZ clock)
            
            // set OCR0A-reg (top value of timer)
            OCR0A = 0x7C;   // dez 124; range 0 - 124 -> 125 cycles till interrupt
            
            // set OCR0B-reg (top value B of timer)
            OCR0B = 124;   // dez 124; range 0 - 124 -> 125 cycles till interrupt
            
            // set prescaler to 1/8
            TCCR0B &= ~(1 << CS02);
            TCCR0B |= (1 << CS01);
            TCCR0B &= ~(1 << CS00);
            break;
    }
    
    TIMSK0 |= (1 << OCIE0B);   // enable Output Compare Match B Interrupt
    TIMSK0 |= (1 << OCIE0A);    // enable Output Compare Match A Interrupt
    TIMSK0 &= ~(1 << TOIE0);    // disable timer overflow interrupt
}

uint16_t Timer_getTick() {
    TIMSK0 &= ~((1 << OCIE0B) | (1 << OCIE0A));   // disable Output Compare Match A,B Interrupt
    
    // store timer_count in a temp int that can't get changed by ISR
    uint16_t temp_timer_count = timer_count;
    
    TIMSK0 |= (1 << OCIE0B) | (1 << OCIE0A);   // enable Output Compare Match A,B Interrupt

    return temp_timer_count;
}

/**
 Timer compare A interrput:
 - increase timer_count
 - if timer_count is at max of uint16, set it to 0
 */
ISR(TIMER0_COMPA_vect){
    timer_count++;
}

volatile uint8_t asdjflk = 0;

ISR(TIMER0_COMPB_vect){
    if ( asdjflk == 0){
        Led7_On();
        Led8_Off();
        asdjflk = 1;
    }else  {
        Led7_Off();
        Led8_On();
        asdjflk = 0;
    }
}


/* Timer_init() aus Aufgabe 1
 void Timer_init() {
     // set mode to normal mode
     TCCR0A &= ~( (1 << WGM01) | (1 << WGM00) );
     TCCR0B &= ~( (1 << WGM02) );
     
     // set prescaler to 1
     TCCR0B &= ~( (1 << CS02) | (1 << CS01) );
     TCCR0B |= (1 << CS00);
     
     // enable interrupt
     TIMSK0 |= (1 << TOIE0);
 }
 */


#include "Uart.h"

/**
 Initialisaton of UART-Port
 - 9600 baud
 - 8 bit data
 - 1 stop-bit
 - no parity
 */
void uart_init() {
    // Set baud rate
    unsigned int baud = 103;    // 103 = 9600 baud (see data sheet page 197)
    UBRR0H = (unsigned char) (baud >> 8);
    UBRR0L = (unsigned char) baud;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // set RX enable and TX enable
    
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // b00000110 -> async USART, no parity, 1 stop-bit, 8 bit (set UCSZn2 in UCSR0C to 0)
    
}
void uart_init_isr() {
    uart_init();
    
    // Data Register Empty Interrupt enable
    UCSR0B |= (1 << UDRIE0);
    
}

ISR(USART0_UDRE_vect){
    if (data to send) {
        send data
    }else {
        UCSR0A &= ~(1 << UDRE0);
    }
}

/**
 Send a String to UART
 (function could be blocking for some time if a large string is passed)
 */
void uart_send(char* string) {
    
    int len = strlen(string);
    
    // Iterate over string
    for (int i = 0; i < len; i++) {
        
        // Wait for transmit register to be empty
        while ( !(UCSR0A & (1 << UDRE0)) )
            ;
        
        // Write byte to transmit register
        UDR0 = string[i];
    }
    
    
}

/**
 Reads one byte from UART-Port and returns it
 */
unsigned char uart_recv() {
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) )
        ;
    /* Get and return received data from buffer */
    return UDR0;
}

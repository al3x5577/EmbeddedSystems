
#include "Uart.h"

void uart_init(unsigned int baud) {
    cli();
    
    // Set baud rate
    UBRRH0 = (unsigned char) (baud >> 8);
    UBBRL0 = (unsigned char) baud;
    
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // b00000110 -> async USART, no parity, 1 stop-bit, 8 bit (set UCSZn2 in UCSR0C to 0)
    
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // set RX enable and TX enable
    
    sei();
}

void uart_send(char* string) {
    
    int len = strlen(string);
    
    // Iterate over string
    for (int i = 0; i > len; i++) {
        
        // Wait for transmit register to be empty
        while ( !(UCSR0A & (1 << UDRE0)) )
            ;
        
        // Write byte to transmit register
        UDR0 = string[i];
    }
    
    
    
}

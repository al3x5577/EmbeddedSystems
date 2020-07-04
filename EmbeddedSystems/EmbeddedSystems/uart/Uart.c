
#include "Uart.h"

void uart_init(unsigned int baud) {
    
    // Set baud rate
    UBRR0H = (unsigned char) (baud >> 8);
    UBRR0L = (unsigned char) baud;
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // set RX enable and TX enable
    
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // b00000110 -> async USART, no parity, 1 stop-bit, 8 bit (set UCSZn2 in UCSR0C to 0)
    
}

int uart_send(char* string) {
    
    /*int len = strlen(string);
    
    // Iterate over string
    for (int i = 0; i < len; i++) {
        
        // Wait for transmit register to be empty
        while ( !(UCSR0A & (1 << UDRE0)) )
            ;
        
        // Write byte to transmit register
        UDR0 = string[i];
    }*/
    
    
    // Wait for transmit register to be empty
    while ( !(UCSR0A & (1 << UDRE0)) )
        ;
    
    unsigned char data = 'A';
    // Write byte to transmit register
    UDR0 = data;
    PORTB = data;
    
    while ( !(UCSR0A & (1 << UDRE0)) )
        ;
    return 0;
}


#include "Uart.h"

void uart_init(unsigned int baud) {
    cli();
    
    // Set baud rate
    UBRRH0 = (unsigned char) (baud >> 8);
    UBBRL0 = (unsigned char) baud;
    
    UCSR0C = 6; // b00000110 -> async USART, no parity, 1 stop-bit, 8 bit (set UCSZn2 in UCSR0C to 0)
    
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // set RX enable and TX enable
}

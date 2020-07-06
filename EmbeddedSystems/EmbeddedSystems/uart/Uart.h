#ifndef MY_UART_H_
#define MY_UART_H_


// Buffer
#ifndef RING_BUFFER_UART_SIZE
#define RING_BUFFER_UART_SIZE 512   // ATmega1284P has 16kB RAM
#endif /* RING_BUFFER_UART_SIZE */
#define BUFFER_FAIL     1
#define BUFFER_SUCCESS  0


#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>

/**
 (Global interrrupt should be disabled while calling this function)
 Initialisaton of UART-Port
 - 9600 baud
 - 8 bit data
 - 1 stop-bit
 - no parity
*/
void uart_init(void);

/**
Initialisiation with ISR (same setting as in uart_init)
Interrupts:
- USART Data Register Empty interrupt
*/
void uart_init_isr(void);

/**
 Send a String to UART
 (function could be blocking for some time if a large string is passed)
*/
void uart_send(char* string);

/**
Non blocking alternative to uart_send.
(Initialisation with ISR has to be called before this!)

String will be stored in buffer (a ring buffer). If buffer is full, theposition of the byte
in string where the buffer was full is returned

Returns:
- 0 if successful
- position in string +1 where the error occured
*/
uint16_t uart_send_isr(char* string);

/**
Reads one byte from UART-Port and returns it
*/
unsigned char uart_recv(void);

/**
Returns 1 if there is data in the buffer, 0 if not
*/
uint8_t buf_available(struct Buffer *buf);

unsigned char uart_get_data(void);

#endif /* MY_UART_H_ */


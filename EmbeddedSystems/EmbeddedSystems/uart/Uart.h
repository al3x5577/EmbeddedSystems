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

// Global interrrupt should be disabled while calling this function
void uart_init(void);
void uart_init_isr(void);

void uart_send(char* string);

unsigned char uart_recv(void);

#endif /* MY_UART_H_ */


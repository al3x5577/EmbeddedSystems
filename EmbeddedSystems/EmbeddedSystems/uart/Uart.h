#ifndef MY_UART_H_
#define MY_UART_H_

#include <avr/io.h>
#include <string.h>


// Global interrrupt should be disabled while calling this function
void uart_init(void);


void uart_send(char* string);

unsigned char uart_recv(void);

#endif /* MY_UART_H_ */


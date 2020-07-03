#ifndef MY_UART_H_
#define MY_UART_H_

#include <avr/io.h>
#include <string.h>


// Global interrrupt should be disabled while calling this function
void uart_init(unsigned int baud);


void uart_send(char* string);

#endif /* MY_UART_H_ */


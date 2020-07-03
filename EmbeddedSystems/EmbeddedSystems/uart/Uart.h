#ifndef MY_UART_H_
#define MY_UART_H_

#include <avr/io.h>
#include <string.h>


void uart_init(void);
void uart_send(char* string);

#endif /* MY_UART_H_ */


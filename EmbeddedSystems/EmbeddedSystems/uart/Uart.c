
#include "Uart.h"

/**
Ring-Buffer
https://www.mikrocontroller.net/articles/FIFO
*/
struct Buffer {
  unsigned char data[RING_BUFFER_UART_SIZE];
  uint16_t read; // points to the oldest byte
  uint16_t write; // points to the first free field
} buffer = {{}, 0, 0};

/**
 Puts a byte to the buffer
 
 Return:
 - BUFFER_FAIL: buffer overflow
 - BUFFER_SUCCESS: byte is put in the buffer
 */
uint8_t buff_put(unsigned char byte)
{

  if ( ( (buffer.write + 1) == buffer.read ) ||
       ( buffer.read == 0 && (buffer.write + 1) == RING_BUFFER_UART_SIZE ) )
    return BUFFER_FAIL; // overflow

  buffer.data[buffer.write] = byte;

  buffer.write++;
    
  if (buffer.write >= RING_BUFFER_UART_SIZE)
    buffer.write = 0;

  return BUFFER_SUCCESS;
}

//
// Holt 1 Byte aus dem Ringbuffer, sofern mindestens eines abholbereit ist
//
// Returns:
//     BUFFER_FAIL       der Ringbuffer ist leer. Es kann kein Byte geliefert werden.
//     BUFFER_SUCCESS    1 Byte wurde geliefert
//
/**
 Takes one byte out of the buffer
 
 Return:
 - BUFFER_FAIL: buffer empty
 - BUFFER_SUCCESS: byte is pulled out and stored in pByte
 */
uint8_t buff_get(unsigned char *pByte)
{
  if (buffer.read == buffer.write)
    return BUFFER_FAIL; // empty

  *pByte = buffer.data[buffer.read];

  buffer.read++;
  if (buffer.read >= RING_BUFFER_UART_SIZE)
    buffer.read = 0;

  return BUFFER_SUCCESS;
}


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
/**
 Initialisiation with ISR
 Interrupts:
 - USART Data Register Empty interrupt
 */
void uart_init_isr() {
    uart_init();
    
    // Data Register Empty Interrupt enable
    UCSR0B |= (1 << UDRIE0);
    
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
 Non blocking alternative to uart_send.
 (Initialisation with ISR has to be called before this!)
 
 String will be stored in buffer (a ring buffer). If buffer is full, theposition of the byte
 in string where the buffer was full is returned
 
 Returns:
 - 0 if successful
 - position in string +1 where the error occured
 */
uint16_t uart_send_isr(char* string) {
    
    int len = strlen(string);
    
    // Iterate over string
    for (int i = 0; i < len; i++) {
        if (buff_put(string[i]) == 1) {
            
            // Enable ISR anyways so that buffer will get empty
            UCSR0A |= (1 << UDRE0);
            
            // Buffer overflow
            return i++;
        }
    }
    
    // Enable ISR
    UCSR0A |= (1 << UDRE0);
    return 0;
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

/**
 ISR for USART Data Register Empty flag
 */
ISR(USART0_UDRE_vect){
    unsigned char pByte;
    // Pull one byte from buffer and store it in pByte
    if (UDR0 == 0 && buff_get(&pByte) == 0) {
        // Send byte
        UDR0 = pByte;
    }else {
        // Buffer empty: disable interrupt
        UCSR0A &= ~(1 << UDRE0);
    }
}

#ifndef TASTER_H_
#define TASTER_H_

#include <avr/io.h>

/*
Initialisiert die Hardware f�r die Taster
*/
void Taster_init(void);

/*
Gibt den aktuellen Status der Tasten aus. 
R�ckgabewert 0 = Taster nicht gedr�ckt, 1 = Taster gedr�ckt.
*/
uint8_t Taster1_get(void);
uint8_t Taster2_get(void);
uint8_t Taster3_get(void);
uint8_t Taster4_get(void);


#endif /* TASTER_H_ */
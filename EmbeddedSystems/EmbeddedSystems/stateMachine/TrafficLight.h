#ifndef TRAFFIC_LIGHT_H_
#define TRAFFIC_LIGHT_H_

#include <avr/io.h>

// if traffic light should use the 8 leds, set extraLeds to 0
// if traffic light should use extra leds, set extrsLeds to 1
void trafficLight(uint8_t extraLeds);

#endif /* TRAFFIC_LIGHT_H_ */

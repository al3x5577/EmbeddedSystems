
#include "TrafficLight.h"

enum {
    AUTO_GREEN_PERSON_RED = 0,
    AUTO_YELLOW_PERSON_RED = 1,
    AUTO_RED_PERSON_RED = 2,
    AUTO_RED_PERSON_GREEN = 4,
    AUTO_RED_PERSON_RED_2 = 5,
    AUTO_YELLOWRED_PERSON_RED = 6
    // state 7 equals 0
} trafficLightWithPerson_state = AUTO_GREEN_PERSON_RED;

uint16_t timeVar = 0;
uint8_t traffic_ready = 1;

void trafficLight() {
    switch (trafficLightWithPerson_state) {
        case AUTO_GREEN_PERSON_RED:
            // set leds
            turnOffD(0);
            turnOffD(1);
            turnOnD(2);
            
            turnOnD(3);
            turnOffD(4);
            
            if((Timer_getTick() - timeVar) >= 30000){
                timeVar = Timer_getTick();
                traffic_ready = 1;
            }
            
            if(traffic_ready && Taster1_get()){
                traffic_ready = 0;
                // goto step 1
                trafficLightWithPerson_state = AUTO_YELLOW_PERSON_RED;
            }
            
            break;
            
        case AUTO_YELLOW_PERSON_RED:
            // set leds
            turnOffD(0);
            turnOnD(1);
            turnOffD(2);
            
            turnOnD(3);
            turnOffD(4);
            
            if((Timer_getTick() - timeVar) >= 5000){
                timeVar = Timer_getTick();
                // goto step 1
                trafficLightWithPerson_state = AUTO_RED_PERSON_RED;
            }
            break;
            
        case AUTO_RED_PERSON_RED:
            // set leds
            turnOnD(0);
            turnOffD(1);
            turnOffD(2);
            
            turnOnD(3);
            turnOffD(4);
            
            if((Timer_getTick() - timeVar) >= 5000){
                timeVar = Timer_getTick();
                // goto step 1
                trafficLightWithPerson_state = AUTO_RED_PERSON_GREEN;
            }
            break;
            
        case AUTO_RED_PERSON_GREEN:
            // set leds
            turnOnD(0);
            turnOffD(1);
            turnOffD(2);
            
            turnOffD(3);
            turnOnD(4);
            
            if((Timer_getTick() - timeVar) >= 30000){
                timeVar = Timer_getTick();
                // goto step 1
                trafficLightWithPerson_state = AUTO_RED_PERSON_RED_2;
            }
            break;
            
        case AUTO_RED_PERSON_RED_2:
            // set leds
            turnOnD(0);
            turnOffD(1);
            turnOffD(2);
            
            turnOnD(3);
            turnOffD(4);
            
            if((Timer_getTick() - timeVar) >= 5000){
                timeVar = Timer_getTick();
                // goto step 1
                trafficLightWithPerson_state = AUTO_YELLOWRED_PERSON_RED;
            }
            break;
            
        case AUTO_YELLOWRED_PERSON_RED:
            // set leds
            turnOnD(0);
            turnOnD(1);
            turnOffD(2);
            
            turnOnD(3);
            turnOffD(4);
            
            if((Timer_getTick() - timeVar) >= 5000){
                timeVar = Timer_getTick();
                // goto step 1
                trafficLightWithPerson_state = AUTO_GREEN_PERSON_RED;
            }
            break;
            
        default:
            break;
    }
}


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
uint8_t button_pressed = 0;

void trafficLight(uint8_t extraLeds) {
    switch (trafficLightWithPerson_state) {
        case AUTO_GREEN_PERSON_RED:
            // set leds
            if (extraLeds) {
                // cars
                turnOffD(0);    // red
                turnOffD(1);    // yellow
                turnOnD(2);     // green
                
                // person
                turnOnD(3);     // red
                turnOffD(4);    // green
            } else {
                // red
                Led2_Off();
                Led3_Off();
                
                // yellow
                Led4_Off();
                Led5_Off();
                
                // green
                Led6_On();
                Led7_On();
                
                // person
                Led1_On();  //red
                Led8_Off();  //green
            }
            
            
            if((Timer_getTick() - timeVar) >= 30000){
                timeVar = Timer_getTick();
                traffic_ready = 1;
            }
            
            if (Taster1_get()) {
                button_pressed = 1;
            }
            
            if(traffic_ready && button_pressed){
                traffic_ready = 0;
                button_pressed = 0;
                
                // goto step 1
                timeVar = Timer_getTick();
                trafficLightWithPerson_state = AUTO_YELLOW_PERSON_RED;
            }
            
            break;
            
        case AUTO_YELLOW_PERSON_RED:
            // set leds
            if (extraLeds) {
                // cars
                turnOffD(0);
                turnOnD(1);
                turnOffD(2);
                
                turnOnD(3);
                turnOffD(4);
            } else {
                // red
                Led2_Off();
                Led3_Off();
                
                // yellow
                Led4_On();
                Led5_On();
                
                // green
                Led6_Off();
                Led7_Off();
                
                // person
                Led1_On();  //red
                Led8_Off();  //green
            }
            
            if((Timer_getTick() - timeVar) >= 5000){
                // goto step 2
                timeVar = Timer_getTick();
                trafficLightWithPerson_state = AUTO_RED_PERSON_RED;
            }
            break;
            
        case AUTO_RED_PERSON_RED:
            // set leds
            if (extraLeds) {
                // cars
                turnOnD(0);
                turnOffD(1);
                turnOffD(2);
                
                turnOnD(3);
                turnOffD(4);
            } else {
                // red
                Led2_On();
                Led3_On();
                
                // yellow
                Led4_Off();
                Led5_Off();
                
                // green
                Led6_Off();
                Led7_Off();
                
                // person
                Led1_On();  //red
                Led8_Off();  //green
            }
            
            if((Timer_getTick() - timeVar) >= 5000){
                timeVar = Timer_getTick();
                trafficLightWithPerson_state = AUTO_RED_PERSON_GREEN;
            }
            break;
            
        case AUTO_RED_PERSON_GREEN:
            // set leds
            if (extraLeds) {
                // cars
                turnOnD(0);
                turnOffD(1);
                turnOffD(2);
                
                turnOffD(3);
                turnOnD(4);
            } else {
                // red
                Led2_On();
                Led3_On();
                
                // yellow
                Led4_Off();
                Led5_Off();
                
                // green
                Led6_Off();
                Led7_Off();
                
                // person
                Led1_Off();  //red
                Led8_On();  //green
            }
            
            if((Timer_getTick() - timeVar) >= 30000){
                timeVar = Timer_getTick();
                trafficLightWithPerson_state = AUTO_RED_PERSON_RED_2;
            }
            break;
            
        case AUTO_RED_PERSON_RED_2:
            // set leds
            if (extraLeds) {
                // cars
                turnOnD(0);
                turnOffD(1);
                turnOffD(2);
                
                turnOnD(3);
                turnOffD(4);
            } else {
                // red
                Led2_On();
                Led3_On();
                
                // yellow
                Led4_Off();
                Led5_Off();
                
                // green
                Led6_Off();
                Led7_Off();
                
                // person
                Led1_On();  //red
                Led8_Off();  //green
            }
            
            if((Timer_getTick() - timeVar) >= 5000){
                timeVar = Timer_getTick();
                trafficLightWithPerson_state = AUTO_YELLOWRED_PERSON_RED;
            }
            break;
            
        case AUTO_YELLOWRED_PERSON_RED:
            // set leds
            if (extraLeds) {
                // cars
                turnOnD(0);
                turnOnD(1);
                turnOffD(2);
                
                turnOnD(3);
                turnOffD(4);
            } else {
                // red
                Led2_On();
                Led3_On();
                
                // yellow
                Led4_On();
                Led5_On();
                
                // green
                Led6_Off();
                Led7_Off();
                
                // person
                Led1_On();  //red
                Led8_Off();  //green
            }
            
            if((Timer_getTick() - timeVar) >= 5000){
                timeVar = Timer_getTick();
                trafficLightWithPerson_state = AUTO_GREEN_PERSON_RED;
            }
            break;
            
        default:
            break;
    }
}

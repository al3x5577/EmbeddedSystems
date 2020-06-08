# EmbeddedSystems
 Repo for Embedded  Systems lecture project.
 (This software is developt for a specific hardware)
 
 ### Hardware setting:
 - CPU: ATMEGA328P U (28 pin)
 - Programmer: diamex ALL-AVR-PROG
 - some leds and buttons
 
 ### Software setting:
 - ATMEL STUDIO 7
 - standard config
 - disabled optimization

## About the project
In this project we want to develop an embedded system based on an ATMEGA1284P.

## Software

### GPIO
The gpio functions help handling the gpios. The board has 4 buttons and 8 leds for user purpose. 

There are to init functions:
- Led_init()
- Taster_init()

to setup the PORTS correctly.

After setup the button states can be accessed by functions:
TasterX_get(), where X is between 1 and 4.

The leds can be controlled with:
- LedX_On()
- LedX_Off()

where X is between 1 and 8.

### Playground
Playground.h provides a playground() function. This function has to be called in a loop.

#### Function
There are four programmes available with the funtion. (One for each button)

The Startup mode is for choosing the program. It is visualised by the led pattern: 10011001. 
To go back to this mode hold button 1 and 2 for max half a second. If you do so, all leds will turn on, then off and then the indicator pattern will show up.

##### Program 1
Button test program. Turns on led1 if button1 is pressed. Same for button2, 3 and 4.

##### Program 2
Board test program. Turns PORTB on and off in intervalls of 500 ms.

##### Program 3
Lauflicht (chaser light) program. 

##### Program 4
Increment / Decrement program. Press button1 to increment, button2 to decrement.


TODO update README.md

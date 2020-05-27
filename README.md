# EmbeddedSystems
 Repo for Embedded  Systems lecture project.
 (This software is developt for a specific hardware)
 
 ### Hardware setting:
 - CPU: ATMEGA328P U (28 pin)
 - Programmer: diamex ALL-AVR-PROG
 - some leds and buttons
 
 ### Software setting:
 - ATMEL STUDIO 7
 - standart config
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
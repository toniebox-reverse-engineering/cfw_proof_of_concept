# Custom Firmware - Proof of Concept
Contains Energia sketches to interact with the various components. Board used in Energia is a customized "CC3200-LAUNCHXL (80Mhz)" board.
Pinout see [Wiki](https://github.com/toniebox-reverse-engineering/toniebox/wiki/Toniebox-CC3200-Pinout)

## Buttons
### Button 1 right ear
Not working, muxed with Serial RX GPIO2
### Button 2 small ear 
Working fine

## LEDs
There is a RGB LED on the board
### LED 1 - Red
TBD is this a pwm pin?
### LED 2 - Blue
Works if power up pin is high
### LED 3 - Green
Working as expected

## SD
Started lib. Not working

## DAC
Started lib. Not working

## RFID
Not yet implemented

## MMA8451Q Accelerometer
POC
I2C 0x1D

## Wifi
Works out of the box

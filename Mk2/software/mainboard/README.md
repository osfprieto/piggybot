# Software for the main board

This is the board that drives the four main engines as well as the consumes data from the sensors.

## Hardware

Board: Elegoo UNO R3 from Smart Robot Kit v2 (2017)
Driver: Arduino/Genuino UNO

## Library requirements

- Infrared comms - [IRRemote](https://www.arduino.cc/reference/en/libraries/irremote/)
  - Validated with version 3.6.1 (pending to update one deprecated function usage)

## Deploying

From the Arduino IDE, deploy to the board.

## Free analog pins

A0 (using it to receive signals from the Microbit board), A1, A2, A3

# STM_GSMWeatherStation - beWeatherAware

## Overview
STM_GSMWeatherStation is a project of stacionary weather station that measures weather conditions in local area and gets condtions in Poznań from the WeatherUnderground web service. 

## Description

The vital component required for project's functioning is STM32f407vg microcontroller. Along with the features of the board itself, project consists of:
* DHT11 - temperature and humidity sensor,
* BMP180 - pressure sensor,
* HD44780 - 2x16 LCD controller,
* FT232R - USB to serial UART interface,
* SIM800C - GSM modem with external source of energy.

Scheme of the whole project:
* [Imgur](http://imgur.com/t8rr7Dd)

## Tools

The entire STM32 software was coded in C using CoIDE:
* [CoIDE 1.7.8](www.coocox.org)

The entire computer-side software was coded in JAVA using IntelliJ IDEA:
* [IntelliJ IDEA](https://www.jetbrains.com/idea/)

## How to run

All you need to do is just wire up everything (all pins are descripted in .h files), compile the code and flash onto the board.
Secondly run the Java code and wait. Everything will be done automitacally.

## How to compile

Use CoIDE to compile C code and to flash program onto the borad. Use IntelliJ to run Java code.

## Future improvements

* We could add some command-line interface to control whole project.
* Replace FT232R USB module with HC-06 Bluetooth module.

## Attributions

We used:
* STM32 libriaries by Tilen Majerle provided on: [stm32f4-discovery](https://stm32f4-discovery.net).
* RXTX library in Java for UART comunication: [RXTX](http://users.frii.com/jarvi/rxtx/download.html).

## License

Distributed under MIT license.

## Credits

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.
Supervisor: Adam Bondyra.

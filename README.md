# Smart-Home-Project-AVR-ATmega32

## Overview
This is an embedded systems project in which a smart home is designed using ATmega32 on Proteus simulation, and can be installed on hardware. It is a common project topic. However, I found it is crucial to conduct this project that uses several hardware drivers, and requires good logic. This smart home can be controlled by two types of users; an admin, who controls the system remotely through a device that uses bluetooth as a phone, represented here using hc-06 bluetooth module, and users who control the smart home directly through the hardware components connected to the microcontroller. You can control 6 rooms lights, with one room having dimmer light, door movement (open/close), Air Conditioner (on/off).


## Drivers Used
MCAL: DIO, I2C, GIE, TIMER0, TIMER1, and UART (Baud Rate:2400)
HAL: LCD< KEYPAD, EEPROM.


## Start
The system starts by showing a message "To start press '0'" on both admin's and users' screens. This is done to ensure serializability of smart home access between the admin (remotely), and users. Either the admin or any user, whoever presses '0' first a session starts to this same person and the other has to wait until this session ends.


## Admin's Actions
* Change password.
* Control 5 rooms Lights (on/off), and one room as dimmer (set percentage).
* Open or close door.
* Turn on or off the AC.
* Add or remove users.


## Users' Actions
* Control 5 rooms Lights (on/off), and one room as dimmer (set percentage).
* Turn on or off the AC.
* Add or remove users.


## Simulation Start
<p align="center">
  <img src="https://user-images.githubusercontent.com/104737465/217668822-d9d5e2f2-3659-4f61-afd1-fc2d5751b984.png" width="700" height="400" title="hover text">
</p>


## Flowchart
[Flowchart.pdf](https://github.com/seifbassiounyy/Smart-Home-Project-AVR-ATmega32-/files/10670031/Flowchart.pdf)

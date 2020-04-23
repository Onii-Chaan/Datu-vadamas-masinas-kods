# Wireless-car
This project is incomplete and have not been completely built/tested!
# Table of contents
- [About]()
    - [Usage]()
- [Setup]()
- [Libraries Used]()
    - [Python]()
    - [Additional Software]()
- [Hardware]()
- [Code]()
    - [Python code]()
    - [Hardware code]()
- [Problems]()
    - [Wireless network]() 
    - [Motor driver IC]()
    - [Completion of project]()
- [Schematic]()

# About
This is circuit and code made for controlling RC car using wireless network by sitting at your PC and pressing simple W A S D keys for driving. 
## Usage
You drive by using W, A, S, D keys from you keyboard. You put your mobile phone on the car so it can record everything that's in front of it. The video is displayed on your PC so you can see where you drive. You don't need to be near this car because phone that's on it is connected to mobile data or local WIFI and receives data from PC.

# Setup
You must have a whole RC car for this project. Take out its PCB and put in this new PCB accordingly. Upload code to Atmega using Arduino as ISP programmer. Download and install ```CarController.aia``` app on your android phone. Run ```serverControllerCode.py``` and input IP and Port into app. After that open screen recording software on your phone and connect it to your PC, so you see what's happening on you phone screen. Connect phone with car bluetooth. Then open camera from CarController app. Connect PCB jack with phone jack. Now you should be good to go. 

# Libraries Used
## Python
- Server code uses ```keyboard``` library for reading keyboard input values.
- Server code uses ```socket``` library for making connections in local network.

## Additional Software
- CarController app must be downloaded and installed on your phone.
- For better performance you can make .exe file from python script.
- Desktop stream software must be downloaded and installed to view video from phone camera.

# Hardware
You must have all the components that are displayed on schematic. Plus, you will need:
- 3.5mm male to male audio jack
- Speaker
- 1 to 2 HC-05 bluetooth modules

# Code
There are 3 code parts, server side, embedded and app code, but only two are described because app were made with MIT App Inventor. 
## Python code
There are 2 codes for python. One is server and other for bluetooth. The bluetooth one is used to use car using HC-05 bluetooth module connected with another Arduino chip.
Server code creates server in local network and gives user IP.
- ```xStop()```, ```yStop()```, ```forward()```, ```backward()``` functions are used for driving car forward and backward and for stopping car when no keys are pressed. To drive forward press W and to backward - S.
- ```left()```, ```right()``` are used to turn left and right with A and D respectively.
- ```audio()``` starts playing siren from car speaker
- ```frontLed()```, ```backLed()``` turns on/off front and back LEDs

## Hardware code
Atmega chip uses UART communication with HC-05 bluetooth module and reads incoming data. Numbers between ```<>``` is read.
- ```<01>```, ```<02>```, ```<00>``` drive forward, backward, stop
- ```<10>```, ```<11>```, ```<12>``` car returns to it default position, left, right
- ```<20>```, ```<21>```, ```<22>``` turn off lights, turn on front lights, turn on back lights 
- ```<30>```, ```<31>``` nothing is played, siren is played
- ```<40>``` request data from car 


# Problems
## Wireless network
## Motor driver IC
## 

# Schematic
![Schematic](https://i.ibb.co/cNR4Rs0/car-scheme.png)

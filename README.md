# Wireless-car
```This project is incomplete and have not been completely built/tested!```
# Table of contents
- [About](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#about)
    - [Usage](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#usage)
- [Setup](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#setup)
- [Libraries Used](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#libraries-used)
    - [Python](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#python)
    - [Additional Software](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#additional-software)
- [Hardware](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#hardware)
- [Code](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#code)
    - [Python code](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#python-code)
    - [Hardware code](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#hardware-code)
    - [Classes and methods](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#classes-and-methods)
- [Problems](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#problems)
    - [Wireless network](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#wireless-network) 
    - [Motor driver IC](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#motor-driver-ic)
- [Completion of project](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#completion-of-project)
- [Schematic](https://github.com/Onii-Chaan/Datu-vadamas-masinas-kods/blob/master/README.md#schematic)

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
# Classes and methods
- ```audioVcc::loop()``` powers LM audio amplifier if audio needs to be played
- ```BTdata::loop()``` listens, processes incoming data and stores it
- ```carLights::turnLights(byte lightState)``` turns on/off car lights
- ```carControl::driveCar(byte mainMotor, byte turnMotor, byte prevTurnMotorVal)``` controlls all motors
- ```gyroData::readAcc()``` reads data from gyroscope and measures battery voltage
# Problems
This project has not been completed. Main problems were with hardware, because THT chip got heated up too much. After building my own H bridge circuit for motor driving, it didn't work and I had too little time to find out the root of the problem. 

## Wireless network
There are difficulities with connecting phone to wireless network. It will work just fine on local network, but I couldn't manage it to work using internet and phone mobile data. One of the reasons was that phone doesn't use static IP address.  

## Motor driver IC
As I said previously L293D THT chip got heated up too much. I put radiator for cooling, but it too got heated up too much. I were not be able to put bigger radiator because there were not that many space left and it made the car heavier causing more current and heat to generate.

## Completion of project
The car do work, although because of motor driver IC heat problem it stops driving after some minutes. I will finish this project someday with SMD PCB, better motor driver IC and better code.  

# Schematic
![Schematic](https://i.ibb.co/cNR4Rs0/car-scheme.png)

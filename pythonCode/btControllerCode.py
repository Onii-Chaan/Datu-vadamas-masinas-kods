import keyboard
from serial import Serial

print("start")

ser = Serial('COM5', baudrate = 9600, timeout =1)

#recMessage = clientsocket.recv(1024).decode()

keyCheck = [0] * 9 #iestata masīva garumu uz 9, jo kopā tiks izmantoti tikai 9 taustiņi, šis ir nepieciešams, lai taustiņš tiktu nospiests tikai vienreiz un tā vērtība netiktu atkārtota mūžīgi
"""
keyCheck atšifrējums:
0 - W uz priekšu
1 - A pa kreisi
2 - S atpakaļ
3 - D pa labi
4 - T ieslēgt/izslēgt signalizāciju
5 - E ieslēgt priekšējās gaismas
6 - R ieslēgt aizmugurējās gaismas
7 - F izslēgt gaismas
8 - C saņemt datus

0 - izslēgts
1 - ieslēgts
"""


#listensocket.send() atliek skriptu uzlabot, lai tas nosūtītu datus
#ja sokets saņem datus, tad saņemtos datus izvada uz ekrāna tikai vienreiz. Nepieciešams loģiskais operators, kas sekos tam vai dati ienāk iekšā vai arī nē

def xStop():
    if not keyboard.is_pressed("w") and not keyboard.is_pressed("s") and keyCheck[0] == 0:
        ser.write(bytes("<00>", "utf-8"))

def yStop():
    if not keyboard.is_pressed("d") and not keyboard.is_pressed("a") and keyCheck[3] == 0:
        ser.write(bytes("<10>", "utf-8"))

def forward():
    if keyboard.is_pressed("w") and not keyboard.is_pressed("s") and keyCheck[0] == 0:
        keyCheck[0] = 1
        ser.write(bytes("<02>", "utf-8"))
    elif not keyboard.is_pressed("w") and keyCheck[0] == 1:
        keyCheck[0] = 0
        xStop()

def backward():
    if keyboard.is_pressed("s") and not keyboard.is_pressed("w") and keyCheck[2] == 0:
        keyCheck[2] = 1
        ser.write(bytes("<01>", "utf-8"))
    elif not keyboard.is_pressed("s") and keyCheck[2] == 1:
        keyCheck[2] = 0
        xStop()

def left():
    if keyboard.is_pressed("d") and not keyboard.is_pressed("a") and keyCheck[3] == 0:
        keyCheck[3] = 1
        ser.write(bytes("<11>", "utf-8"))
    elif not keyboard.is_pressed("d") and keyCheck[3] == 1:
        keyCheck[3] = 0
        yStop()

def right():
    if keyboard.is_pressed("a") and not keyboard.is_pressed("d") and keyCheck[1] == 0:
        keyCheck[1] = 1
        ser.write(bytes("<12>", "utf-8"))
    elif not keyboard.is_pressed("a") and keyCheck[1] == 1:
        keyCheck[1] = 0
        yStop()

def audio():
    if keyboard.is_pressed("t") and keyCheck[4] == 0:
        while keyboard.is_pressed("t"):
            True
        keyCheck[4] = 1
        ser.write(bytes("<31>", "utf-8"))
    elif keyboard.is_pressed("t") and keyCheck[4] == 1:
        while keyboard.is_pressed("t"):
            True
        keyCheck[4] = 0
        ser.write(bytes("<30>", "utf-8"))

def frontLed():
    if keyboard.is_pressed("e") and not keyboard.is_pressed("f") and keyCheck[5] == 0:
        keyCheck[5] = 1
        ser.write(bytes("<21>", "utf-8"))
    elif not keyboard.is_pressed("e") and keyCheck[5] == 1:
        keyCheck[5] = 0

def backLed():
    if keyboard.is_pressed("r") and not keyboard.is_pressed("f") and keyCheck[6] == 0:
        keyCheck[6] = 1
        ser.write(bytes("<22>", "utf-8"))
    elif not keyboard.is_pressed("r") and keyCheck[6] == 1:
        keyCheck[6] = 0


def offLed():
    if keyboard.is_pressed("f") and not keyboard.is_pressed("r") and keyCheck[7] == 0 and not keyboard.is_pressed("e"):
        keyCheck[7] = 1
        ser.write(bytes("<20>", "utf-8"))
    elif not keyboard.is_pressed("f") and keyCheck[7] == 1:
        keyCheck[7] = 0


def recData():
    if keyboard.is_pressed("c") and keyCheck[8] == 0:
        keyCheck[8] = 1
        ser.write(bytes("<40>", "utf-8"))
    elif not keyboard.is_pressed("c") and keyCheck[8] == 1:
        keyCheck[8] = 0

def keyboardListener():
    forward()
    backward()
    left()
    right()
    audio()
    frontLed()
    backLed()
    offLed()
    recData()

while True: # cikls atkārtojas mūžīgi
    keyboardListener()
    
    



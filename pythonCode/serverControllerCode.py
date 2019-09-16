import keyboard
print("start")

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

def forward():
    if keyboard.is_pressed("w") and not keyboard.is_pressed("s") and keyCheck[0] == 0:
        keyCheck[0] = 1
        print("w")
    elif not keyboard.is_pressed("w") and keyCheck[0] == 1:
        keyCheck[0] = 0
        print("no w")

def backward():
    if keyboard.is_pressed("s") and not keyboard.is_pressed("w") and keyCheck[2] == 0:
        keyCheck[2] = 1
        print("s")
    elif not keyboard.is_pressed("s") and keyCheck[2] == 1:
        keyCheck[2] = 0
        print("no s")

def left():
    if keyboard.is_pressed("d") and not keyboard.is_pressed("a") and keyCheck[3] == 0:
        keyCheck[3] = 1
        print("d")
    elif not keyboard.is_pressed("d") and keyCheck[3] == 1:
        keyCheck[3] = 0
        print("no d")

def right():
    if keyboard.is_pressed("a") and not keyboard.is_pressed("d") and keyCheck[1] == 0:
        keyCheck[1] = 1
        print("a")
    elif not keyboard.is_pressed("a") and keyCheck[1] == 1:
        keyCheck[1] = 0
        print("no a")

def audio():
    if keyboard.is_pressed("t") and keyCheck[4] == 0:
        while keyboard.is_pressed("t"):
            True
        keyCheck[4] = 1
        print("audio on")
    elif keyboard.is_pressed("t") and keyCheck[4] == 1:
        while keyboard.is_pressed("t"):
            True
        keyCheck[4] = 0
        print("audio off")

def frontLed():
    if keyboard.is_pressed("e") and not keyboard.is_pressed("f") and keyCheck[5] == 0:
        keyCheck[5] = 1
        print("e")
    elif not keyboard.is_pressed("e") and keyCheck[5] == 1:
        keyCheck[5] = 0
        print("test frontLed not pressed")

def backLed():
    if keyboard.is_pressed("r") and not keyboard.is_pressed("f") and keyCheck[6] == 0:
        keyCheck[6] = 1
        print("r")
    elif not keyboard.is_pressed("r") and keyCheck[6] == 1:
        keyCheck[6] = 0
        print("test backLed not pressed")


def offLed():
    if keyboard.is_pressed("f") and not keyboard.is_pressed("r") and keyCheck[7] == 0 and not keyboard.is_pressed("e"):
        keyCheck[7] = 1
        print("f")
    elif not keyboard.is_pressed("f") and keyCheck[7] == 1:
        keyCheck[7] = 0
        print("test offLed not pressed")


def recData():
    if keyboard.is_pressed("c") and keyCheck[8] == 0:
        keyCheck[8] = 1
        print("c")
    elif not keyboard.is_pressed("c") and keyCheck[8] == 1:
        keyCheck[8] = 0
        print("no recData")

while True: # cikls atkārtojas mūžīgi
    forward()
    backward()
    left()
    right()
    audio()
    frontLed()
    backLed()
    offLed()
    recData()

""""
NEPIECIEŠAMĀS KEYBOARD BIBLIOTĒKAS DAĻAS

keyboard.is_pressed("a")

"""    

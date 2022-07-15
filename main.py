import keyboard
import math
import serial

port = input("Serial port?")
"""ser = serial.Serial(port, 9600)
ser.flushInput()"""

#qewdpommnghtjhzcvasdttgfgjihfe

diffInd = 0
diffLet = 'a'
meg = ''

keys = "qazwsxedcrfvtgbyhnujmikolp"

def indToLed(k):
    return (math.ceil((keys.index(k)/len(keys) + .01 )*8))


def liss():
    global diffInd
    global diffLet

    for i in range(0, len(keys)):
        if (keyboard.is_pressed(keys[i])):
            if((diffInd != indToLed(keys[i])) or (diffLet != keys[i])):
                diffInd = indToLed(keys[i])
                diffLet = keys[i]
                #ser.write.encode(diffInd)
                print(diffInd)

while 1:
    liss()

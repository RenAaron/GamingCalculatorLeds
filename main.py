import keyboard
import serial
import math

port = input("Serial port?")
ser = serial.Serial(port, 9600)
ser.flushInput()

#DSDGLFFJWWODJDLLFKDKFFKDLSDLDL

diffInd = 0
diffLet = 'a'

keys = "qazwsxedcrfvtgbyhnujmikolp"

def indToLed(k):
    return (math.ceil((keys.index(k)/len(keys) + .01 )*8))


def liss():
    global diffInd, diffLet, ser

    for i in range(0, len(keys)):
        if (keyboard.is_pressed(keys[i])):
            if((diffInd != indToLed(keys[i])) or (diffLet != keys[i])):
                ser.write(str(diffInd).encode())
                diffInd = indToLed(keys[i])
                diffLet = keys[i]
                print(diffInd)

while 1:
    liss()

import keyboard
import math

#qewdpommnghtjhzcv

diffInd = 0
diffLet = 'a'

keys = "qazwsxedcrfvtgbyhnujmikolp"

def indToLed(k):
    return (math.ceil((keys.index(k)/len(keys) + .01 )*8))


def liss():
    global diffInd
    global diffLet

    for i in range(0, len(keys)):
        if (keyboard.is_pressed(keys[i])):
            if(diffInd != indToLed(keys[i])):
                diffInd = indToLed(keys[i])
                print (diffInd)
            if(diffLet != keys[i]):
                diffLet = keys[i]
                print(diffLet)

while 1:
    liss()

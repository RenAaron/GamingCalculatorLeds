import keyboard
import math

#wqwertyuioq

diffInd = 0
diffNum = 'a'

keys = "qazwsxedcrfvtgbyhnujmikolp"

print(math.ceil((keys.index('p')/len(keys) + .01 )*8))
print(math.ceil((keys.index('d')/len(keys) + .01 )*8))


def indToLed(k):
    return (math.ceil((keys.index(k)/len(keys) + .01 )*8))


def liss():
    global diffInd

    for i in range(0, len(keys)):
        if (keyboard.is_pressed(keys[i])):
            if(diffInd != indToLed(keys[i])):
                diffInd = indToLed(keys[i])
                print (diffInd)
            print("pressed")

while 1:
    liss()
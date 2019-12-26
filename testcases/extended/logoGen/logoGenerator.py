from PIL import Image
import os
import sys
import numpy as np

filename = sys.argv[1]
with Image.open(filename) as img:
    data = np.array(img)
    h, w = data.shape[0], data.shape[1]
    print("@SIZE {} {}".format(w, h))
    print("@BACKGROUND 255 255 255")
    print("@POSITION 0 0")
    print("MOVE {}".format(h-1))
    print('TURN 90')

    for i in range(h):
        for j in range(w):
            print('COLOR', data[i][j][0], data[i][j][1], data[i][j][2])
            # print('COLOR', data[i][j][0], data[i][j][0], data[i][j][0])
            print('MOVE 1')
        print('CLOAK')
        print('TURN 180')
        print('MOVE {}'.format(w))
        print('TURN -90')
        print('MOVE 1')
        print('TURN -90')

    # print(data.shape)

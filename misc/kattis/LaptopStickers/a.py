[length, height, nums] = map(int, input().split())
letter = ord('a')

M = [['_' for i in range(height)] for j in range(length)]

for num in range(nums):
    # yit = 0 #y iterator
    [x, y, startx, starty] = map(int, input().split())
    for yvalue in range(y):
        for xvalue in range(x):
          if (startx + xvalue < length and starty + yvalue < height):
            M[startx + xvalue][starty + yvalue] = chr(letter)
    letter += 1

for j in range(height):
    for i in range(length):
        print(M[i][j], end='')
    print()

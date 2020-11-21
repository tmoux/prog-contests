from __future__ import print_function
from collections import deque
import os
import sys
from atexit import register
from io import BytesIO

sys.stdin = BytesIO(os.read(0, os.fstat(0).st_size))
sys.stdout = BytesIO()
register(lambda: os.write(1, sys.stdout.getvalue()))

input = lambda: sys.stdin.readline().rstrip('\r\n')

ret = deque()
prep = []

def prepend():
    global ret
    global prep
    if len(prep) > 0:
        for c in reversed(prep):
            ret.appendleft(c)
        prep = []

T = int(input())
for i in range(T):
    s = list(input())
    #while s[-1] == '\n' or s[-1] == '\r': s.pop()
    ret = deque()
    prep = []
    mode = 0
    for c in s:
        if c == '<':
            if mode == 0:
                if len(ret) > 0: ret.pop()
                elif len(prep) > 0: prep.pop()
            elif (len(prep) > 0): prep.pop()
        elif c == '[':
            if (mode == 0):
                mode = 1
            else:
                prepend()
        elif c == ']':
            if (mode == 1):
                mode = 0
                prepend()
        else:
            if mode == 0: ret.append(c)
            else: prep.append(c)
    prepend()
    #print s
    for c in ret:
        print(c,end='')
    print('')

import sys
input = sys.stdin.readline

target = [1,1,2,2,2,8]
inp = [int(x) for x in input().split()]
for i in range(6):
    print(target[i]-inp[i],end=' ')

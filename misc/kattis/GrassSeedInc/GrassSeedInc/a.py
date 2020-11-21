import sys
input = sys.stdin.readline

C = float(input())
L = int(input())
acc = 0
for i in range(L):
    [w,l] = [float(x) for x in input().split()]
    acc += C*w*l
print(acc)

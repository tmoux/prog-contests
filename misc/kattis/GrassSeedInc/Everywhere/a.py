import sys
input = sys.stdin.readline

T = int(input())
for i in range(T):
    n = int(input())
    names = set()
    for i in range(n):
        name = input()
        names.add(name)
    print(len(names))

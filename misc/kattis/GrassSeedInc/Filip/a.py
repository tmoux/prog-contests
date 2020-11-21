import sys
input = sys.stdin.readline

[A,B] = [int(x) for x in input().split()]
A = (A%10)*100 + ((A/10)%10)*10 + (A/100)%10
B = (B%10)*100 + ((B/10)%10)*10 + (B/100)%10
print(max(A,B))

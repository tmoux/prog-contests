N = int(input())
used = {}
for _ in range(N):
    X = int(input())
    if X <= 1000000:
        used[X] = 0

for i in range(0, N+1):
    if not i in used:
        print(i)
        break

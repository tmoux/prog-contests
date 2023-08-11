T = int(input())
for _ in range(T):
    [n, m] = map(int, input().split())
    arr = [list(map(int, input().split())) for i in range(n)]

    best = 0
    D = [(-1, -1), (-1, 1), (1, -1), (1, 1)]
    for i in range(n):
        for j in range(m):
            total = arr[i][j]
            for (dx, dy) in D:
                d = 1
                while 0 <= i+d*dx < n and 0 <= j+d*dy < m:
                    total += arr[i+d*dx][j+d*dy]
                    d += 1
            best = max(best, total)
    print(best)

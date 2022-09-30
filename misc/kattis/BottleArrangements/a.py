T = int(input())
for _ in range(T):
    [n, m] = map(int, input().split())
    R = 0
    W = 0
    for i in range(m):
        [r, w] = map(int, input().split())
        R = max(R, r)
        W = max(W, w)
    if (R + W > n):
        print("IMPOSSIBLE")
    else:
        extra = n - (R + W)
        R += extra
        print(('R' * R) + ('W' * W))


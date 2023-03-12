def check(N, b):
    m = 1
    while N > 0:
        mod = N % (m * b)
        if (mod == 0 or mod == m):
            N -= mod
            m *= b
        else:
            return False
    return True

def solve(N):
    K = 8
    ans = 0
    for mask in range(2**K):
        c = []
        for i in range(K):
            c.append(mask >> i & 1)

        # print(c)
        def evaluate(x):
            return (c[0] - N) + (c[1] * x) + (c[2] * x * x) + (c[3] * x * x * x) + (c[4] * x * x * x * x) + (c[5] * x * x * x * x * x) + (c[6] * x * x * x * x * x * x) + (c[7] * x * x * x * x * x * x * x)
        lo = 0
        hi = N+1
        # for i in range(lo, hi+1):
        #     print(i, evaluate(i))
        while lo + 1 < hi:
            mid = (lo + hi) // 2
            if evaluate(mid) <= 0:
                lo = mid
            else:
                hi = mid

        # print(lo, evaluate(lo))
        if lo > 1 and evaluate(lo) == 0:
            ans += 1
            # print("Counting", mask)

    b = 2
    while (b * b * b * b * b * b * b * b <= N):
        if check(N, b):
            ans += 1
        b += 1

    return ans

T = int(input())
for tt in range(T):
    N = int(input())
    print("solving", tt)
    print(solve(N))

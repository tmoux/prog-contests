from collections import defaultdict

N = int(input())
A = list(map(int, input().split()))

totalCnt = 0
totalSum = 0

cnt = defaultdict(int)
ans = 0
for i in range(N):
    curCnt = totalCnt
    curSum = totalSum
    for x in range(A[i]-1, A[i]+2):
        curCnt -= cnt[x]
        curSum -= x * cnt[x]
    ans += curCnt * A[i] - curSum

    cnt[A[i]] += 1
    totalCnt += 1
    totalSum += A[i]

print(ans)

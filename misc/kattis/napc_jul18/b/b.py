import sys

N, T, K = map(int,sys.stdin.readline().split())
c = [i+5 for i in range(K)]
for i in range(K):
   c[i] = int(sys.stdin.readline())

def countWithCost(C, k):
    res = 0
    for i in range(k):
        d = max(0,(C-c[i])//T + 1)
        sq = 2*d*(d+1)+1
        res += max(0,sq-2)
    return res

def calcWithFloors(k):
    ans = 0
    n = N
    for i in range(k):
        if n > 0:
            ans += c[i]
            n -= 1

    lo = 0
    hi = 2000000*T + 2000000000
    while lo + 1 < hi:
        mid = (lo+hi)//2
        cnt = countWithCost(mid, k)
        if cnt <= n:
            lo = mid
        else:
            hi = mid
    cost = lo

    for i in range(k):
        d = max(0,(cost-c[i])//T + 1)
        if d > 0:
            sq = 2*d*(d+1)+1
            num = sq-2
            dist_cost = (4*(d+1)*(d)*(d-1)//3)*T
            init_cost = c[i]*num

            n -= num
            assert(n >= 0)
            ans += dist_cost + init_cost

    ans += (cost+1)*n
    return ans;


lo = 0
hi = K
while hi - lo > 1:
    mid = (lo+hi)//2
    if calcWithFloors(mid) < calcWithFloors(mid+1):
        hi = mid
    else:
        lo = mid
ans = calcWithFloors(lo+1)
print(ans)

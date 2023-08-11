import sys

T = int(sys.stdin.readline())
for _ in range(T):
    [n, k, x] = map(int, sys.stdin.readline().split())
    x -= 1
    s = sys.stdin.readline()

    v = []
    cnt = 0
    for i in range(n):
        if s[i] == 'a': continue
        cnt += 1
        if s[i] == '*' and (i == n-1 or s[i+1] == 'a'):
            v.append(cnt*k+1)
            cnt = 0

    prods = [x+1 for i in range(len(v))]
    prod = 1
    for i in reversed(range(len(v))):
        prods[i] = prod
        prod *= v[i]

        if prod > x:
            break

    # print(v)
    # print(prods)
    ans = []
    for i in prods:
        take = x // i
        x -= take * i
        ans.append(take)

    # print(ans)
    pt = 0

    ret = ""
    for i in range(n):
        if s[i] == 'a':
            ret += 'a'
        elif s[i] == '*' and (i == n-1 or s[i+1] == 'a'):
            for j in range(ans[pt]):
                ret += 'b'
            pt += 1
    sys.stdout.write(ret+"\n")

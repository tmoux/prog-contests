T = int(input())
for a in range(T):
    N, K = (int(s) for s in input().split())
    S = input()
    zeros = list(i for i in range(N) if S[i] == '0')
    ones = list(i for i in range(N) if S[i] == '1')
    for i in range((N-K+1) // 2):
        if not ones:
            zeros.pop(0)
        else: ones.pop(0)
    for i in range((N-K) // 2):
        if not zeros:
            ones.pop(0)
        else: zeros.pop(0)
    b = zeros + ones
    b.sort()
    for i in b: print(S[i],end='')
    print("")

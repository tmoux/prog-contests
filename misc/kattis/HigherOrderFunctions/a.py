import sys
sys.setrecursionlimit(40000)
S = input()
N = len(S)

def prim(i):
    global S
    if i >= N:
        return (-1, -1)
    p = exp(i+1)
    if p[0] != -1:
        return (p[0], p[1] + 1)
    elif i+1 < N and S[i] == '(' and S[i+1] == ')':
        return (0, i+2)
    else:
        return (-1, -1)

def exp(i):
    global S
    if i >= N or S[i] != '(':
        return (-1, -1)
    p = prim(i)
    if p[1] < N and S[p[1]] == '-':
        p2 = exp(p[1]+2)
        return (max(p[0]+1, p2[0]), p2[1])
    else:
        return p

ans = exp(0)[0]
print(ans)

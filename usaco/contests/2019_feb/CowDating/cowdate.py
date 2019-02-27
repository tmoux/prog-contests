from decimal import *
import math
getcontext().prec = 200
a = []
def getans(r):
    b = []
    for i in range(r):
        b.append(a[i])
    b.sort()
    ans = Decimal(0)
    prod = Decimal(1)
    s = Decimal(0)
    for i in reversed(b):
        prod = prod * Decimal((Decimal(1)-Decimal(Decimal(i)/Decimal(1000000))))
        s = s + Decimal(i)/(Decimal(1)-Decimal(i)/Decimal(1000000))
        r = prod * s
        ans = max(ans,r)
    return ans


fin = open("cowdate.in","r")
fout = open("cowdate.out","w")
N = int(fin.readline().strip())
for i in range(N):
    b = int(fin.readline().strip())
    a.append(b)

ans = Decimal(0)
for i in range(1,N+1):
    ans = max(ans,getans(i))
fout.write('{0:.0f}'.format(ans))



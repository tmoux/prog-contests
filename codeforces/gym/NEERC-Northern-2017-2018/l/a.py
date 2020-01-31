import sys
import math

sys.stdin=open("little.in","r")
sys.stdout=open("little.out","w")

def mult(li):
    r = 1;
    for i in li:
        r *= i
    return r

n = int(input())
cp = n
while (cp % 2 == 0):
    cp /= 2
if (cp == 1):
    print(-1)
else:
    ret = []
    for i in range(1,70):
        rt = math.floor(n**(1.0/i))
        while (rt**i > n): 
            rt -= 1
        while ((rt+1)**i <= n): 
            rt += 1
        #print(i,rt)
        li = [rt] * i
        if (mult(li) == n):
            ret.append(li)
            continue
        for j in range(i):
            li[j] = rt+1;
            if mult(li) == n:
                ret.append(li)
                break
            if mult(li) > n:
                break
    print(len(ret))
    for li in ret:
        print(len(li),end=" ")
        for i in li:
            print(i,end=" ")
        print("")

import math
x = int(input())
def getAns():
    lo = 1
    hi = x
    while (lo + 1 < hi):
        mid = (lo+hi)//2
        if (mid*mid) < x:
            lo = mid
        elif (mid*mid > x):
            hi = mid
        elif (mid*mid == x):
            return mid
    return lo
print(getAns())

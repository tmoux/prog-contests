from math import floor
def s(x):
    r = 0
    m = 3
    while (x**(1/m) >= 2):
        f = floor(x**(1/m))
        r += f
        m += 1
        print(m-1,f)
    return r

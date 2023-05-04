for i in range(10):
    print(sum(j*j*j for j in range(i)))

def f(l, r):
    s = 0;
    for i in range(l, r+1):
        for j in range(i+1, r+1):
            s += i*j
    return s

def g(l, r):
    s = 0;
    for i in range(l, r+1):
        for j in range(i+1, r+1):
            for k in range(j+1, r+1):
                s += i*j*k
    return s

def d(n):
    return sum(1 if n % i == 0 else 0 for i in range(1,n+1))
def sumf(n, f):
    return sum(f(i) if n % i == 0 else 0 for i in range(1,n+1))

for i in range(1,20):
    print(i,d(i),sumf(i,d))

x0 = 0
x1 = 4;
x2 = 4*x1 - 3*x0;
n = 2;
while x2 % 83 != 0:
    x0 = x1
    x1 = x2
    x2 = 4*x1 - 3*x0
    n += 1
print(x2,n)

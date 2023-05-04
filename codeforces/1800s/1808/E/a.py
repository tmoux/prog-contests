#!/usr/bin/env python3

def f(n):
    return (6 ** n - ((-1) ** n) * (2 ** (n))) / 8

def g(k, n):
    return ((k - 1) ** n + (k - 1) * (-1) ** n) / k

for i in range(10):
    print(i, g(5, i))

from math import factorial

l = 0
for i in range(1, 5982+1):
    print(i)
    l += len(str(factorial(i)))
print(l)

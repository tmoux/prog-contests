def mat_mul(a, b):
    c = []
    for i in range(len(a)):
        c.append([0]*len(b[0]))
        for j in range(len(b[0])):
            for k in range(len(a[0])):
                c[i][j] += (a[i][k]*b[k][j])
    return c

def mat_pow(a, n):
    l = len(a)
    res = [[0 for i in range(l)] for j in range(l)]
    for i in range(l):
        res[i][i] = 1
    while n > 0:
        if n % 2 == 1:
            res = mat_mul(res, a)
        a = mat_mul(a, a)
        n = n // 2
    return res

A = [[1 for i in range(9)] for i in range(9)]
for k in range(9):
    A[k][(9 - k) % 9] += 1

B = [[0] for i in range(9)]
B[0][0] = 1
print(A)
# print(mat_mul(mat_pow(A, 100000), B))
a = int('1' * 10000)
print(a)

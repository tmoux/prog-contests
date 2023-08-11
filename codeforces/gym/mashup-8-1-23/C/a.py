N, K = map(int, input().split())

num = 1
for i in range(2 ** N, 2 ** N - K, -1):
    print(format(i, '010b'))
    num *= i

print(num)
cnt = 0
while num % 2 == 0:
    num = num // 2
    cnt += 1
print(num)

print(2 ** (N * K))
x = N
G = 2
while K >= G:
    print("Adding", (K-1) // G)
    x += (K-1) // G
    G *= 2
print(x, cnt)

K = int(input())
ans = 1
prev = 0
for i in range(K):
    x = int(input())
    if (x < prev): ans += 1
    prev = x
print(ans)

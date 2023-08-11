mx = 0
for a in range(11):
    for b in range(11):
        x = (2 ** a) * (3 ** b)
        if x <= 1000:
            print(a + 2 * b)
            mx = max(mx, a + 2 * b)
print(2 * mx)

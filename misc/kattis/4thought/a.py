# tags: io, dictionaries, lists
ops = [("+", "+"), 
       ("-", "-"), 
       ("*", "*"), 
       ("//", "/")]

MAX = 1000000
# We want to store strings for indices from -MAX to MAX,
# but since negative indices cycle around the back, we can
# just create an array of length 2 * MAX + 1.
# Also this array is very sparse, but I wanted to demonstrate how this problem can be solved without dictionaries.
d = [""] * (MAX * 2 + 1)

for (o1, c1) in ops:
    for (o2, c2) in ops:
        for (o3, c3) in ops:
            s = f'4 {o1} 4 {o2} 4 {o3} 4'
            try:
                x = eval(s)
                if -MAX <= x <= MAX:
                    d[x] = f'4 {c1} 4 {c2} 4 {c3} 4 = {x}'
            except:
                pass

m = int(input())
for _ in range(m):
    x = int(input())
    print(d[x]) if d[x] else print("no solution")

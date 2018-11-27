# Read in cases to consider
cases = int(input())

for i in range(0, cases):
    inputs = input().split()
    a = int(inputs[0])
    b = int(inputs[1])
    print(a*b)

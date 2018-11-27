# Scan in number of cases
cases = int(input())

# Prime seive
primes = [True] * 51
for factor in range(2, 51):
    if primes[factor]:
        temp = factor+factor

        while temp <= 50:
            primes[temp] = False
            temp += factor

# Perfect squares sieve
squares = [False] * 51
for root in range(0, 8):
    squares[root*root] = True

for i in range(1, cases+1):
    restaurants = int(input())
    nameList = []
    count = 0

    for j in range(0, restaurants):
        saved = input()
        current = saved.lower()

        vowels = 0.0
        chars = 0

        # Character checker
        for character in current:
            if character == 'a' or character == 'e' or character == 'i' or character == 'o' or character == 'u':
                vowels += 1.0
            elif character == 'y':
                vowels += .5
            chars += 1

        # Validity checker
        if int(vowels) == vowels and ((primes[chars] and int(vowels)%2 != 0) or (squares[chars] and squares[int(vowels)])):
            nameList.append(saved)
            count += 1

    if count == 0:
        print("Practice #", i, ": It's hopeless!", sep="")
    else:
        print("Practice #", i, ": ", count, " valid options", sep="")
    for rest in nameList:
        print(rest)
    print()

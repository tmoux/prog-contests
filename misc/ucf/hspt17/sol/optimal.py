# Written by Will Cromar
# Python 3.6

from math import ceil, sqrt
from array import array
from itertools import permutations

# Run a prime sieve to save time later
N = int(1e7 + 1)
isPrime = array('b', (True for _ in range(N)))
isPrime[0] = isPrime[1] = False

# If factor is not prime, mark its multiples not prime
for factor in range(2, ceil(sqrt(N))):
    if isPrime[factor]:
        for multiple in range(factor * factor, N, factor):
            isPrime[multiple] = False

# Process each test case
b = int(input())
for battle in range(b):
    x = input().strip()

    # Re-arrange the digits of x in all possible ways
    perms = ["".join(perm) for perm in permutations(x)]
    # Eliminate permuations with leading 0's and x itself
    perms_valid = [perm for perm in perms if perm != x and not perm.startswith('0')]

    # If x is prime and any permutation is prime, then the autobots win
    if isPrime[int(x)] and any(isPrime[perm] for perm in map(int, perms_valid)):
        print("Battle #%d: Autobots, roll out!" % (battle + 1))
    # Otherwise, they're doomed
    else:
        print("Battle #%d: Oh no, the autobots are doomed!" % (battle + 1))
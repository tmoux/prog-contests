#!/usr/bin/env python3
import sys
MOD = 998244353

input = sys.stdin.readline

def main():
    m, k = map(int, input().split())
    coeff = [2 for _ in range(k + 1)]
    coeff[1] = 1

    # do all the inclusion exclusion up front
    # use 2 as a sentinel value for a prime d
    # repeated prime factor => 0
    # odd # of prime factors => -1
    # even # of prime factors => 1
    for d in range(2, k + 1):
        if abs(coeff[d]) == 2:
            coeff[d] = -1
            for j in range(d * d, k + 1, d * d):
                coeff[j] = 0
            for j in range(2 * d, k + 1, d):
                if coeff[j] == 2:
                    coeff[j] = -1
                else:
                    coeff[j] = -coeff[j]

    # include all 0
    ret = 1
    for j in range(1, k + 1):
        # dont include all 0
        ret += (coeff[j] * (pow(2 * (k // j) + 1, m, MOD) - 1)) % MOD
        ret %= MOD

    print(ret)

if __name__ == '__main__':
    main()

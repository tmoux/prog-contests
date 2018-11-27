# Written by Will Cromar
# Python 3.6

from math import radians, pi, sqrt

def solve(r, homes):
    # Returns the minimum arc length of alpha
    def arclen(alpha):
        return r * min(alpha, 2 * pi - alpha)

    # Given a bunker location, sum the distances each caterpillar must move
    def sumDist(bunker):
        return sum(arclen(abs(pos - bunker)) for pos in homes)

    # Try the home of each caterpillar as the bunker location
    return min(map(sumDist, homes))

# Process each case
t = int(input())
for case in range(t):
    # Read in radius and homes
    r, c = map(int, input().split())
    homes = map(float, input().split())
    homes = map(radians, homes)

    ans = solve(r, list(homes))
    print("Tree #%d: %.3f" % (case + 1, ans))

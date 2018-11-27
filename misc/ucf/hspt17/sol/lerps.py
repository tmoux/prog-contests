# Written by Will Cromar
# Python 3.6

# An iterator of all rooms that have an even sum to the left
# and right. Essentially, a list of all potentially optimal
# sacrafices
def sacrafices(freq):
    # Keep track of the sum of lerps to the left and right
    left = 0
    right = sum(freq)
    for cnt in freq:
        # If all lerps to the left and right can be saved,
        # yield this element
        right -= cnt

        if left % 2 == 0 and right % 2 == 0:
            yield cnt

        left += cnt

# Process each case
t = int(input())
for case in range(t):
    # Read in the number of lerps in each room
    n = int(input())
    freq = list(map(int, input().strip().split()))

    # Find the total number of lerps
    tot = sum(freq)

    # If the total numer of lerps is even, we can just break down
    # all of the walls and save all of the lerps
    if tot % 2 == 0:
        ans = tot
    # Otherwise, we need to choose a room with an odd number of
    # lerps to sacrafice and save the rest
    else:
        ans = tot - min(sacrafices(freq))

    print("Environment #%d: %d lerps" % (case + 1, ans))

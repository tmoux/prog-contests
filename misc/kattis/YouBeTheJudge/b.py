def valid_num(s):
    if all('0' <= c and c <= '9' for c in s):
        if (s[0] != '0' or len(s) == 1):
            return True
            # x = int(s)
            # return 2 <= x and x <= 1000000000
    return False

def isprime(x):
    if (x < 2): return False
    for i in range(2, x):
        if i*i > x: break
        if x % i == 0: return False
    return True

nums = []
while True:
    try:
        words = input().strip().split()
        for word in words:
            if not valid_num(word):
                print(0)
                quit()
            else:
                nums.append(int(word))
    except EOFError:
        break

if len(nums) == 3 and nums[0] % 2 == 0 and 3 <= nums[0] and nums[0] <= 1000000000 and isprime(nums[1]) and isprime(nums[2]) and nums[0] == nums[1] + nums[2]:
    print(1)
else:
    print(0)

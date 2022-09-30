def main(): 
    tokens = []
    while True:
      try:
        line = input().split()
        if line:
            for word in line:
                tokens.append(word)
      except EOFError:
        break
    nums = []
    for tok in tokens:
        # if not tok.isdigit():
        #    return 0
        if tok[0] == "0":
            return 0
        try:
            num = int(tok)
            nums.append(num)
        except ValueError:
            return 0
    if len(nums) != 3:
        return 0
    if nums[0] <= 3 or nums[0] > 10**9 or nums[0]%2 != 0:
        return 0
    if isPrime(nums[1]) and isPrime(nums[2]):
        if nums[1]+ nums[2] == nums[0]:
            return 1
    return 0

import math
def isPrime(n):
    if n <= 1:
        return False
    for i in range(2,int(math.sqrt(n))+1):
        if (n%i) == 0:
            return False
    return True
  
print(str(main()))

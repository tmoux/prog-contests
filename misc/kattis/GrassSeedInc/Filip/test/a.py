nums = input().split()
num0Str = nums[0]
num1Str = nums[1]
nums[0] = int(nums[0])
nums[1] = int(nums[1])
digit = []
digit1 = []
for i in range(2):
    num = nums[i]
    rem = num%10
    digits = []
    while(rem):#loop puts digits into arrays
        digits.append(rem)
        num = (num-rem)/10
        rem = num%10
    if (i):
        digit1 = digits.copy()
    else:
        digit = digits.copy()
 
ans = 0
for i in range(len(digit1)):
    if (digit[i]>digit1[i]):
        ans = num0Str
        break
    elif (digit1[i]>digit[i]):
        ans = num1Str
        break
print(ans)

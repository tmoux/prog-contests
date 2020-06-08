def getPal(s):
    if (len(s) == 1):
        return s
    elif (s == "10"):
        return "9"
    elif (len(s) == 2):
        return str(int(s)/11*11)
    elif (len(s) > 2):
        mid = (len(s)+1)/2
        ah = int(s[0:mid])
        ah -= 1
        t = str(ah)
        if len(s) % 2 == 0:
            return t + t[::-1]
        else:
            return t + t[len(t)-2::-1]
    else:
        return s


t = int(input())
for q in range(t):
    s = str(input())
    ns = int(s)
    ans = []
    while (ns > 0):
        pal = getPal(s)
        ans.append(pal)
        ns -= int(pal)
        s = str(ns)
    print(len(ans))
    for i in ans:
        print(i)

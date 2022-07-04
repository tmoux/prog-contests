T = int(input())
for i in range(T):
    n = int(input())
    D = int(input())
    add = int('1' + ('0' * (n-1)))
    D += add
    if len(str(D)) == n:
        P = int('1' + ('0' * (n-1)) + '1')
    else:
        P = int('1' + ('1' * (n-1)) + '1')
    ans = P - (D - add)
    assert(len(str(ans)) == n)
    print(ans)

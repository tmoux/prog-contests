#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int sumdiv(int x) {
    int res = 0;
    for (int i = 1; i <= x; i++) {
        if (x % i == 0) res += i;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << sumdiv(6) << '\n';
    for (int i = 1; i <= 10000; i++) {
        if (sumdiv(i) == 432) cout << i << '\n';    
    }

    return 0;
}


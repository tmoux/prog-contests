#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n = 2333;
    cout << n << '\n';
    for (int i = 1; i <= n; i++) {
        if (i&1) cout << i << ' ';
        else cout << 0 << ' ';
    }
    cout << '\n';
    for (int i = 1; i <= n; i++) {
        if (!(i&1)) cout << i << ' ';
        else cout << 0 << ' ';
    }

}


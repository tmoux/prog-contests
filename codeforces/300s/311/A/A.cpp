#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    ll tot = 1LL*n*(n-1)/2;
    if (tot <= k) {
        cout << "no solution\n";
    }
    else {
        for (int i = 0; i < n; i++) {
            cout << 0 << ' ' << i << '\n';
        }
    }
}


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    ll ans = 0;
    for (int i = 2; i <= n; i++) {
        int r = 0;
        for (int j = 2; j*j <= i; j++) {
            if (i % j == 0) {
                r += i/j;
                if (j*j != i) r += j;
            }
        }
        ans += 4*r;
    }
    cout << ans << '\n';

    return 0;
}


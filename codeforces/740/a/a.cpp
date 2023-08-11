#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, a, b, c; cin >> n >> a >> b >> c;
    ll ans = 1e18;
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 10; j++) {
            for (int k = 0; k <= 10; k++) {
                ll cost = 1LL*i*a + 1LL*j*b + 1LL*k*c;
                int num = n + i + 2*j + 3*k;
                if (num % 4 == 0) {
                    ans = min(ans,cost);
                }
            }
        }
    }
    cout << ans << '\n';
}


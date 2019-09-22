#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int c[maxn], w[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    ll ans = 0;
    multiset<int> s;
    for (int i = 0; i < n; i++) {
        if (c[i] % 100 == 0) {
            continue;
        }
        else {
            int mod = c[i] % 100;
            if (m >= mod) {
                m -= mod;
                s.insert(w[i]);
                cout << i << ": change free\n";
            }
            else {
                int mn = *s.begin();
                if (mn < w[i]) {
                    cout << i << ": taking " << mn << '\n';
                    s.erase(s.begin());
                }
                else {
                    //eat the cost
                    ans += 1LL*w[i]*(100-mod);
                    m += (100-mod);
                    cout << i << ": eating cost\n";
                }
            }
        }
    }
    cout << ans << '\n';
}


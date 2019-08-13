#include <bits/stdc++.h>
using namespace std;
using ll = long long;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll n, m, k; cin >> n >> m >> k;
        vector<ll> h(n);
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        bool poss = true;
        for (int i = 0; i < n - 1; i++) {
            if (h[i] >= h[i+1]-k) {
                m += (h[i]-max(0LL,h[i+1]-k));
            }
            else {
                ll needed = max(0LL,h[i+1]-h[i]-k);
                if (needed > m) {
                    poss = false;
                    break;
                }
                else {
                    m -= needed;
                }
            }
        }
        cout << (poss ? "YES" : "NO") << '\n';
    }

}


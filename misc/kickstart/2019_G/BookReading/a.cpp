#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int sum[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        int n, m, q; cin >> n >> m >> q;
        memset(sum,0,sizeof sum);
        for (int i = 0; i < m; i++) {
            int p; cin >> p;
            for (int j = 1; j*j <= p; j++) {
                if (p % j == 0) {
                    sum[j]++;
                    if (p/j != j) sum[p/j]++;
                }
            }
        }
        ll ans = 0;
        while (q--) {
            int ri; cin >> ri;
            ans += (n/ri) - sum[ri];
        }
        cout << ans << '\n';
    }
}


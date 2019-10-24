#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int K = 51;
int cnt[K][2];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        memset(cnt,0,sizeof cnt);
        cout << "Case #" << qq << ": ";
        int n;
        ll m; cin >> n >> m;
        for (int i = 0; i < n; i++) {
            ll ai; cin >> ai;
            for (int j = 0; j < K; j++) {
                if (ai & (1LL<<j)) cnt[j][1]++;
                else cnt[j][0]++;
            }
        }
        for (int i = 0; i < K; i++) {
            m -= (1LL<<i) * min(cnt[i][0],cnt[i][1]);
        }
        if (m < 0) {
            cout << -1 << '\n';
        }
        else {
            ll k = 0;
            for (int i = K-1; i >= 0; i--) {
                if (cnt[i][1] >= cnt[i][0]) {
                    k += (1LL<<i);
                }
                else {
                    if (m-((1LL<<i)*(cnt[i][0]-cnt[i][1])) >= 0) {
                        m -= (1LL<<i)*(cnt[i][0]-cnt[i][1]);
                        k += (1LL<<i);
                    }
                }
            }
            cout << k << '\n';
        }
    }
}


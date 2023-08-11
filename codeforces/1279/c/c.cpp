#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
int a[maxn], b[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        map<int,int> depth;
        set<pair<int,int>> s;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            depth[a[i]] = i;
        }
        for (int i = 1; i <= m; i++) {
            cin >> b[i];
            s.insert({depth[b[i]],b[i]});
        }
        vector<bool> done(n+1,false);
        ll ans = 0;
        for (int i = 1; i <= m; i++) {
            if (done[b[i]]) continue;
            int k = depth[b[i]] - i;
            //cout << i << ": " << k << endl;
            ans += 2*k+1;
            while (!s.empty()) {
                auto p = *s.begin();
                s.erase(s.begin());
                if (p.second == b[i]) break;
                else {
                    done[p.second] = true;
                    ans++;
                }
            }
        }
        cout << ans << '\n';
    }
}


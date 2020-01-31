#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<pair<int,int>> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i].first >> v[i].second;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            vector<pair<int,int>> u;
            int cur = 0;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                u.push_back(v[j]);
            }
            sort(u.begin(),u.end());
            int mxr = -1;
            for (int j = 0; j < u.size(); j++) {
                if (mxr < u[j].first) cur++;
                mxr = max(mxr,u[j].second);
            }
            ans = max(ans,cur);
        }
        cout << ans << '\n';
    }
}


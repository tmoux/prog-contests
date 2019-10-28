#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5+5;
int n;
int ord[N];
ll pre[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        vector<pair<int,int>> v;
        for (int i = 0; i < n; i++) {
            int m, p; cin >> m >> p;
            v.push_back({m,p});
        }
        sort(v.begin(),v.end());
        pre[0] = v[0].second;
        for (int i = 1; i < n; i++) {
            pre[i] = pre[i-1] + v[i].second;
        }
        ll ans = 0;
        int curr = 0;
        multiset<int> ms; //ones not bought yet
        for (int i = n-1; i >= 0; i--) {
            //cout << v[i].first << ' ' << v[i].second << '\n';
            ms.insert(v[i].second);
            if (i+curr < v[i].first) {
                ans += *ms.begin();
                ms.erase(ms.begin());
                curr++;
            }
        }
        cout << ans << '\n';
    }
}


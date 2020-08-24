#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        mp[ai]++;
    }
    vector<pair<int,int>> v;
    for (auto p: mp) v.push_back({p.second,p.first});
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    vector<int> a;
    for (auto p: v) {
        for (int j = 0; j < p.first; j++) {
            a.push_back(p.second);
        }
    }
    vector<int> b = a;
    rotate(b.begin(),b.begin()+v[0].first,b.end());
    int ans = 0;
    for (int i = 0; i < n; i++) if (a[i] != b[i]) ans++;
    cout << ans << '\n';
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ' << b[i] << '\n';
    }
}

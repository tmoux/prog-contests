#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    map<int,int> cnt;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        cnt[ai]++;
    }
    vector<int> v;
    for (auto p: cnt) {
        v.push_back(p.second);
    }
    sort(v.begin(),v.end());
    int ans = 0;
    for (int i = 0; i < (int)v.size()-k; i++) {
        ans += v[i];
    }
    cout << ans << '\n';
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> p(n), pos(n);
    const int M = 998244353;
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        ans += n-i;
    }
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        --p[i];
        pos[p[i]] = i;
    }
    vector<int> v;
    for (int i = 0; i < k; i++) {
        v.push_back(pos[n-i-1]);
    }
    sort(v.begin(),v.end());
    ll ways = 1;
    for (int i = 1; i < v.size(); i++) {
        ways = (ways*(v[i]-v[i-1])) % M;
    }
    cout << ans << ' ' << ways << '\n';
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, d; cin >> n >> d;
    vector<int> a(n);
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    map<int,int> quotients;
    for (auto p: mp) {
        quotients[p.first/d] += p.second;
    }
    ll ans = 0;
    for (auto p: quotients) {
        ans += 1LL*p.second*(p.second-1)/2;
    }
    cout << ans << '\n';
}


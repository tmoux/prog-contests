#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int hi; cin >> hi;
        v.push_back(hi);
    }
    sort(v.begin(),v.end());
    ll ans = 0;
    for (int i = 0; i < n-k; i++) {
        ans += v[i];
    }
    cout << ans << endl;
}


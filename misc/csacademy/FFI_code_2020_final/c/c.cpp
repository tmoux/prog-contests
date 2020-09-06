#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    ll X; 
    cin >> n >> X;
    int mid = n/2;
    vector<ll> a, b;
    for (int i = 0; i < mid; i++) {
        ll ai; cin >> ai;
        a.push_back(ai);
    }
    for (int i = mid; i < n; i++) {
        ll ai; cin >> ai;
        b.push_back(ai);
    }
    map<ll,vector<ll>> mp;
    for (int i = 0; i < (1<<mid); i++) {
        ll sum = 0;    
        vector<ll> v;
        for (int j = 0; j < mid; j++) {
            if (i&(1<<j)) {
                sum += a[j];    
                v.push_back(a[j]);
            }
        }
        mp[sum] = v;
    }
    int m = n-mid;
    for (int i = 0; i < (1<<m); i++) {
        ll sum = 0;
        vector<ll> v;
        for (int j = 0; j < m; j++) {
            if (i&(1<<j)) {
                sum += b[j];
                v.push_back(b[j]);
            }
        }
        if (mp.count(X-sum)) {
            cout << (mp[X-sum].size() + v.size()) << '\n';
            for (auto x: mp[X-sum]) {
                cout << x << ' ';
            }
            for (auto x: v) {
                cout << x << ' ';
            }
            cout << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 305;
int n, l[maxn], c[maxn];
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    map<int,ll> mp;
    for (int i = 0; i < n; i++) {
        for (auto p: mp) {
            int gc = __gcd(p.first,l[i]);
            if (gc < p.first) {
                if (!mp.count(gc)) {
                    mp[gc] = INF;
                }
                mp[gc] = min(mp[gc],(ll)p.second+c[i]);
            }
        }
        if (!mp.count(l[i])) {
            mp[l[i]] = INF;
        }
        mp[l[i]] = min(mp[l[i]],(ll)c[i]);
    }
    if (!mp.count(1)) {
        cout << -1 << '\n';
    }
    else {
        cout << mp[1] << '\n';
    }
}


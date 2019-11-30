#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n, a[maxn], b[maxn], c[maxn];

map<vector<int>,int> mp;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a[i] = ai & ((1<<15)-1);
        b[i] = ai & (((1<<15)-1)<<15);
    }
    for (int x = 0; x < (1<<15); x++) {
        vector<int> v;
        for (int i = 0; i < n; i++) {
            v.push_back(__builtin_popcount(a[i]^x));
        }
        mp[v] = x;
    }
    for (int x = 0; x < (1<<15); x++) {
        int y = x<<15;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            v.push_back(__builtin_popcount(b[i]^y));
        }
        for (int sz = 0; sz <= 30; sz++) {
            vector<int> need;
            for (int i = 0; i < n; i++) {
                need.push_back(sz-v[i]);
            }
            if (mp.count(need)) {
                int ans = y | mp[need];
                cout << ans << '\n';
                return 0;
            }
        }
    }
    cout << -1 << '\n';
}

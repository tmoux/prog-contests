#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        map<int,int> mp;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            ++mp[ai];
        }
        int ans = 0;
        for (auto p: mp) {
            ans = max(ans,min(p.second,(int)mp.size()-1));
            ans = max(ans,min(p.second-1,(int)mp.size()));
        }
        cout << ans << '\n';
    }
}

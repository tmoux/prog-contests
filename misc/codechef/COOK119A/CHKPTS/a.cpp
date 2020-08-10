#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n;
        ll c; 
        cin >> n >> c;
        auto MOD = [c](ll x) {
            return ((x%c)+c)%c;
        };
        vector<ll> x(n), y(n);
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
        map<ll,vector<int>> mp;
        for (int i = 0; i < n; i++) {
            mp[y[i]-x[i]].push_back(i);
        }
        int numCheckpoints = 0;
        ll numMoves = 0;
        for (auto& v: mp) {
            map<ll,vector<ll>> mod;
            for (auto i: v.second) {
                mod[MOD(x[i])].push_back(x[i]);
            }
            for (auto& u: mod) {
                numCheckpoints++;
                sort(u.second.begin(),u.second.end());
                int sz = u.second.size();
                ll med = u.second[sz/2];
                for (auto j: u.second) {
                    numMoves += abs(j-med)/c;
                }
            }
        }
        cout << numCheckpoints << ' ' << numMoves << '\n';
    }
}

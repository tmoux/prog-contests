#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<int,pair<int,int>> mp;
const int M = 998244353;
ll powmod(ll base, int p) {
    ll res = 1;
    while (p) {
        if (p&1) res = (res * base) % M;
        base = (base * base) % M;
        p >>= 1;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (!mp.count(ai)) {
            mp[ai] = {i,i};
        }
        else {
            mp[ai].second = i;
        }
    }
    vector<pair<int,int>> vs;
    for (auto p: mp) vs.push_back(p.second);
    sort(vs.begin(),vs.end(),[](auto a, auto b) {
            return a.first < b.first; });
    int cnt = 0;
    for (int i = 1; i < vs.size(); i++) {
        if (vs[i].first < vs[i-1].second) {
            vs[i].second = max(vs[i].second,vs[i-1].second);
        }
        else {
            cnt++;
        }
    }
    cout << powmod(2,cnt) << '\n';

    return 0;
}


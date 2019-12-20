#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
map<int,vector<pair<int,int>>> v;

ll dist(pair<int,int> a, pair<int,int> b) {
    return abs(a.first-b.first) + abs(a.second-b.second);
}

ll dp[maxn][2]; //0: ending at front, 1: ending at back
vector<pair<int,int>> r[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v[max(x,y)].push_back({x,y});
    }
    v[0].push_back({0,0});
    r[0] = v[0];
    int pt = 1;
    for (auto& p: v) {
        vector<pair<int,int>>& vec = p.second;
        sort(vec.begin(),vec.end(),[](auto a, auto b) {
            int mx = max(a.first,a.second);
            return a.first + (mx-a.second) < b.first + (mx-b.second); });
        auto st = vec[0];
        auto en = vec.back();
        ll d = dist(st,en);
        dp[pt][0] = min(dp[pt-1][0]+dist(r[pt-1][0],en),
                        dp[pt-1][1]+dist(r[pt-1].back(),en)) + d;
        dp[pt][1] = min(dp[pt-1][0]+dist(r[pt-1][0],st),
                        dp[pt-1][1]+dist(r[pt-1].back(),st)) + d;
        r[pt] = vec;
        pt++;
    }
    ll ans = min(dp[pt-1][0],dp[pt-1][1]);
    cout << ans << '\n';
}


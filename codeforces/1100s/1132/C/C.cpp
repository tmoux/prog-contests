#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n, q;
pair<int,int> v[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        cin >> v[i].first >> v[i].second;
    }
    sort(v+1,v+q+1,[](auto a, auto b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second > b.second;
            });
    vector<pair<int,int>> ps;
    ps.push_back(v[1]);
    int taken = 0;
    for (int i = 2; i <= q; i++) {
        if (v[i].second <= ps.back().second) {
            taken++;
        }
        else {
            ps.push_back(v[i]);
        }
    }
    int prev = 0;
    int total = 0;
    for (auto p: ps) {
        total += p.second - max(prev+1,p.first) + 1;
        prev = p.second;
    }
    if (taken >= 2) {
        cout << total << '\n';
        return 0;
    }
    else {
        int ans = 0;
        int N = ps.size();
        ps.insert(ps.begin(),{0,0});
        ps.push_back({n+1,n+1});
        for (int i = 1; i <= N; i++) {
            int loss = max(ps[i+1].first-1-(ps[i-1].second+1)+1,0);
            
        }
    }
}

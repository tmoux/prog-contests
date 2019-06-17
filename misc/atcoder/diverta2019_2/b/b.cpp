#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int get(set<pair<int,int>> s, int a, int b) {
    int ans = 0;
    while (!s.empty()) {
        auto p = *s.begin();
        s.erase(s.begin());
        ans++;
        while (s.count({p.first-a,p.second-b})) {
            s.erase({p.first-a,p.second-b});
            p = {p.first-a,p.second-b};
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    set<pair<int,int>> s;
    vector<pair<int,int>> v;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        s.insert({x,y});
        v.push_back({x,y});
    }
    int ans = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a = v[i].first-v[j].first;
            int b = v[i].second-v[j].second;
            if (a != 0 || b != 0) ans = min(ans,get(s,a,b));
        }
    }
    cout << ans << '\n';
}


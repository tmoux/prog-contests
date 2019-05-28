#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;

map<pair<int,int>,int> cnt;
vector<pair<int,int>> oc;

map<int,vector<pair<int,int>>> oks;

int getHighest(int x) {
    for (int i = 0; i < oc.size(); i++) {
        if (oc[i].second == x || cnt.count(make_pair(x,oc[i].second))) {
            continue;
        }
        return oc[i].first;
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    map<int,int> occ;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        cnt[make_pair(a,b)]++;
        cnt[make_pair(b,a)]++;
        occ[a]++;
        occ[b]++;
    }
    for (auto& p: cnt) {
        pair<int,int> q = p.first;
        int num = p.second;
        oks[q.first].push_back({q.second,num});
    }
    for (auto& p: occ) {
        oc.push_back({p.second,p.first});
    }
    sort(oc.begin(),oc.end(),greater<pair<int,int>>());
    for (int i = 1; i <= n; i++) {
        if (!occ.count(i)) continue;
        int maxans = occ[i] + getHighest(i);
        for (auto& p: oks[i]) {
            maxans = max(maxans,occ[i] + occ[p.first] - p.second);
        }
        if (maxans == m) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
}


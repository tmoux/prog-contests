#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m;
struct Edge
{
    int to, c;
};
vector<Edge> dirs[maxn];
map<pair<int,int>,vector<int>> mp;

pair<pair<int,int>,vector<int>> poss(int x, bool finish) {
    //perform top sort, if cycles    
    vector<int> indegree(n+1,0);
    for (int i = 1; i <= n; i++) {
        for (Edge e: dirs[i]) {
            if (e.c <= x) continue; //small edges are deleted
            indegree[e.to]++;
        }
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) if (indegree[i] == 0) q.push(i);
    vector<int> tops, top_order(n+1,0);
    while (!q.empty()) {
        int f = q.front(); q.pop();
        tops.push_back(f);
        top_order[f] = tops.size();
        for (Edge e: dirs[f]) {
            if (e.c <= x) continue;
            if (--indegree[e.to] == 0) {
                q.push(e.to);
            }
        }
    }
    if (tops.size() < n) return {{-1,-1},{}};                    
    if (!finish) return {{x,0},{}};
    vector<int> ans;
    set<pair<int,int>> pp;
    for (int i = 1; i <= n; i++) {
        for (Edge e: dirs[i]) {
            if (top_order[e.to] < top_order[i]) //wrong way
                pp.insert(make_pair(i,e.to));
        }
    }
    for (auto p: pp) {
        for (int i: mp[p]) {
            ans.push_back(i);
        }
    }
    return {{x,ans.size()},ans};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        dirs[u].push_back({v,c});
        mp[make_pair(u,v)].push_back(i + 1);
    }
    int lo = -1, hi = 1e9+9;
    pair<pair<int,int>,vector<int>> ans;
    while (lo + 1 < hi) {
        int m = (lo+hi)/2;
        auto p = poss(m,false);
        if (p.first.first == -1) {
            lo = m;
        }
        else {
            ans = p;
            hi = m;
        }
    }
    ans = poss(hi,true);
    //output ans
    sort(ans.second.begin(),ans.second.end());
    ans.second.erase(unique(ans.second.begin(),ans.second.end()),ans.second.end());
    cout << ans.first.first << ' ' << ans.second.size() << '\n';
    for (int i: ans.second) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m;
struct Edge { int to; bool work; };
vector<Edge> adj[maxn];
int previous[maxn], dist[maxn], num[maxn];

set<pair<int,int>> s;
struct E
{
    int u, v;
    bool is;
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, z; cin >> x >> y >> z;
        adj[x].push_back({y,z});
        adj[y].push_back({x,z});
        if (z) s.insert({x,y});
    }
    //simple bfs, minimizing number of broken paths we take
    queue<int> q;
    q.push(1);
    for (int i = 1; i <= n; i++) dist[i] = maxn+100;
    dist[1] = 0;
    while (!q.empty()) {
        int f = q.front();
        for (Edge e: adj[f]) {
            int j = e.to;
            int d = e.work ? 0 : 1;
            if (dist[f] + 1 < dist[j] || (dist[f] + 1 == dist[j] && num[f] + d < num[j])) {
                previous[j] = f;
                dist[j] = dist[f] + 1;
                num[j] = num[f] + d;
                q.push(j);
            }
        }
        q.pop();
    }

    //The rest below is just formatting the STUPID answer!
    vector<pair<int,int>> v;
    int curr = n;
    while (curr != 1) {
        v.push_back({curr,previous[curr]});
        curr = previous[curr];
    }

    //get answer
    vector<E> ans;
    for (auto p: v) {
        if (!s.count(p) && !s.count({p.second,p.first})) {
            ans.push_back({p.first,p.second,1});
        }
        else {
            auto it = s.find(p);
            if (it != s.end()) s.erase(it);
            it = s.find({p.second,p.first});
            if (it != s.end()) s.erase(it);
        }
    }
    for (auto p: s) {
        ans.push_back({p.first,p.second,0});
    }
    //output
    cout << ans.size() << '\n';
    for (E e: ans) {
        cout << e.u << ' ' << e.v << ' ' << (e.is ? 1 : 0) << '\n';
    }

    return 0;
}


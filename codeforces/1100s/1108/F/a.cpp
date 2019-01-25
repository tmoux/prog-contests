#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
struct Edge
{
    int u, v, weight;
};

int parent[maxn]; //memset to -1
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    assert(x != y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n >> m;
    deque<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges.push_back({u,v,w});
    }
    sort(edges.begin(),edges.end(),[](auto& a, auto& b) {
            return a.weight < b.weight;
            });
    //go through the edges in sorted order, take out all the ones with the same weight. Take one, add the rest back to the front with added weight, and increase the answer
    int ans = 0;
    while (!edges.empty()) {
        Edge e = edges.front(); edges.pop_front();
        vector<Edge> currs = {e};
        while (!edges.empty() && edges.front().weight == e.weight) {
            currs.push_back(edges.front());
            edges.pop_front();    
        }
        vector<int> vv(currs.size(),0);
        for (int i = 0; i < currs.size(); i++) {
            int upar = Find(currs[i].u);
            int vpar = Find(currs[i].v);
            if (upar == vpar) vv[i] = 1;
            //cout << currs[i].u << ' ' << currs[i].v << ' ' << currs[i].weight << ' ' << vv[i] << '\n';
        }
        //cout << '\n';
        for (int i = 0; i < currs.size(); i++) {
            if (vv[i] == 0) {
                int upar = Find(currs[i].u);
                int vpar = Find(currs[i].v);
                if (upar == vpar) {
                    ans++;
                }
                else {
                    Union(currs[i].u,currs[i].v);
                    //cout << currs[i].u << ' ' << currs[i].v << '\n';
                }
            }
        }
    }
    cout << ans << '\n';

    return 0;
}


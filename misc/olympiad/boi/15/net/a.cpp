#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n;
int deg[maxn];
int subtree[maxn];

int pre[maxn];
int low[maxn];
bool v[maxn];

int point = 0;

struct Edge
{
    int to, id;
};
vector<Edge> adj[maxn];

bool hasBridge = false;

void go(int now, int fromID) {
    if (hasBridge) return;
    pre[now] = point++;
    v[now] = true;
    low[now] = pre[now];
    bool isArt = false;
    int childCnt = 0;
    for (int i = 0; i < adj[now].size(); i++) {
        if (adj[now][i].id == fromID) continue;
        int to = adj[now][i].to;
        if (v[to]) {
            //to must be an ancestor of now
            low[now] = min(low[now],pre[to]);
        }
        else {
            //bold edge going downwards
            go(to,adj[now][i].id);
            childCnt++;
            low[now] = min(low[now],low[to]);
            if (low[to] >= pre[now]) {
                isArt = true;
            }
            if (pre[now] < low[to]) {
                hasBridge = true;
            }
        }
    }
    if (fromID == -1) {
        isArt = childCnt != 1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    srand(time(NULL));
    cin >> n;
    vector<pair<int,int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        ++deg[a];
        ++deg[b];
        edges.push_back({a,b});
    }
    vector<int> leafs;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) leafs.push_back(i);
    }
    while (true) {
        point = 0;
        memset(v,false,sizeof v);
        memset(pre,0,sizeof pre);
        memset(low,false,sizeof low);
        hasBridge = false;
        random_shuffle(leafs.begin(),leafs.end());
        int id = 0;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        for (int i = 0; i < n - 1; i++, id++) {
            adj[edges[i].second].push_back({edges[i].first,id});
            adj[edges[i].first].push_back({edges[i].second,id});
        }
        for (int i = 0; i < leafs.size(); i += 2, id++) {
            int nxt = leafs[(i+1)%leafs.size()];
            adj[leafs[i]].push_back({nxt,id});
            adj[nxt].push_back({leafs[i],id});
        }
        go(1,-1);
        if (!hasBridge) {
            //output
            cout << ((leafs.size()+1)/2) << '\n';
            for (int i = 0; i < leafs.size(); i += 2, id++) {
                int nxt = leafs[(i+1)%leafs.size()];
                cout << leafs[i] << ' ' << nxt << '\n';
            }
            return 0;
        }
    }
}

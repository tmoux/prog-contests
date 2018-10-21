#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 250050;
int n, k, m;
vector<int> adj[maxn], token[maxn];
bool vis[maxn];
int res = 0, indegree[maxn];

struct Node
{
    set<int>* s;
    inline int sz() { return s->size(); }
    Node() { s = new set<int>; }
};

void merge(Node& a, Node& b) {
    if (a.sz() < b.sz()) swap(a,b);
    for (int i: (*b.s)) {
        a.s->insert(i);
    }
}

Node* dfs(int i, int p) {
    vis[i] = true;
    Node* ni = new Node();    
    for (int j: adj[i]) {
        if (j == p) continue;
        Node* nj = dfs(j,i);
        merge(*ni,*nj);
    }
    bool is = false;
    for (int t: token[i]) {
        if (ni->s->count(t)) {
            is = true;
        }
    }
    for (int t: token[i]) {
        ni->s->insert(t);
    }
    if (is) {
        res++;
        ni->s->clear();
    }
    return ni;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> m;
    for (int i = 0; i < k; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }
    for (int i = 0; i < m; i++) {
        int s, t; cin >> s >> t;
        token[s].push_back(i);
        token[t].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i] && indegree[i] == 0) {
            dfs(i,i);
        }
    }
    cout << res << '\n';
    return 0;
}

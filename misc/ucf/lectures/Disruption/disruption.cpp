#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 500005;
int n, m;
vector<int> adj[maxn];
vector<pair<int,int>> repl[maxn];
map<pair<int,int>,int> ans;
pair<int,int> order[maxn];

struct Node
{
    set<pair<int,int>>* s;
    inline int sz() {return s->size();}
    Node() {
        s = new set<pair<int,int>>;
    }
    void add(pair<int,int>& p) {
        if (s->count(p)) {
            s->erase(p);
        }
        else {
            s->insert(p);
        }
    }

    int getans() {
        if (sz() == 0) {
            //no active nodes
            return -1;
        }
        return (*s->begin()).first;
    }

} nodes[maxn];

void merge(Node& a, Node& b) {
    if (a.sz() < b.sz()) {
        swap(a,b);
    }
    for (pair<int,int> p: (*b.s)) {
        a.add(p);
    }
    delete b.s;
}

void dfs(int i, int par) {
    nodes[i] = Node();
    for (int j: adj[i]) {
        if (j == par) continue;
        dfs(j,i);
        merge(nodes[i],nodes[j]);
    }
    for (pair<int,int>& a: repl[i]) {
        nodes[i].add(a);
    }
    if (par != -1) {
        ans[make_pair(i,par)] = nodes[i].getans();
        ans[make_pair(par,i)] = ans[make_pair(i,par)];
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        order[i] = {u,v};
    }
    for (int i = 0; i < m; i++) {
        int p, q, r; cin >> p >> q >> r;
        repl[p].push_back({r,i});
        repl[q].push_back({r,i});
    }
    dfs(1,-1);

    for (int i = 0; i < n - 1; i++) {
        cout << ans[order[i]] << '\n';
    }

    return 0;
}
	


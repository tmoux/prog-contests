#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 1000007;
vector<int> adj[maxn];
int n, ans[maxn];

struct Node
{
    int id;
    vector<int>* depth;
    int maxx, idx;
    inline int sz() {return depth->size();}
    Node() {}
    Node(int i) {
        id = i;
        depth = new vector<int>(0);
        maxx = -1;
        idx = -1;
    }
    void add(int pos, int num) {
        (*depth)[pos] += num;
        if ((*depth)[pos] > maxx || ((*depth)[pos] == maxx && pos > idx)) {
            maxx = (*depth)[pos];
            idx = pos;
        }
    }
    void addLast(int num) {
        depth->push_back(num);
        if (depth->back() >= maxx) {
            maxx = depth->back();
            idx = sz()-1;
        }
    }
} nodes[maxn];

void merge(Node& lhs, Node& rhs) {
    if (rhs.sz() > lhs.sz()) swap(lhs,rhs);
    int diff = lhs.sz() - rhs.sz();
    for (int i = 0; i < rhs.sz(); i++) {
        lhs.add(i + diff, (*rhs.depth)[i]);
    }
}

void dfs(int i, int par) {
    nodes[i] = Node(i);    
    for (int j: adj[i]) {
        if (j != par) {
            dfs(j,i);
            merge(nodes[i],nodes[j]);
            //nodes[i].merge(nodes[j]);
        }
    }
    nodes[i].addLast(1);
    ans[i] = nodes[i].sz() - nodes[i].idx - 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,-1);
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
    return 0;
}
	


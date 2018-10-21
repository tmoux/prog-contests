#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, k;
vector<int> adj[maxn];
bool isG[maxn];
ll ans = 0;

struct Node
{
    vector<vector<int>>* vec;
    bool type;
    int curr;
    inline int sz() {return vec->size();}
    Node() {};
    Node(bool is) {
        vec = new vector<vector<int>>;
        type = is;
        curr = 0;
    }
    void addSelf() {
        if (!type) {
            vec->push_back({1,0});
        }
        else {
            vec->push_back({0,1});
        }
    }
} nodes[maxn];

void merge(Node& a, Node& b) {
    if (a.type != b.type) return;
    if (a.sz() < b.sz()) {
        swap(a,b);
    }
    
    int diff = a.sz() - b.sz();
    for (int i = 0; i < b.sz(); i++) {
        (*a.vec)[i+diff][a.type] += (*b.vec)[i][a.type];
    }
}

void dfs(int i, int par) {
    nodes[i] = Node(isG[i]);
    for (int j: adj[i]) {
        if (j == par) continue;
        dfs(j,i);
        merge(nodes[i],nodes[j]);
    }
    nodes[i].addSelf();
    ans += nodes[i].curr;
    nodes[i].curr++;
    cout << i << ":\n";
    for (int j = 0; j < nodes[i].sz(); j++) {
        cout << (*nodes[i].vec)[j][0] << ":" << (*nodes[i].vec)[j][1] << ' ';
    }
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        isG[i] = c == 'G';
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,-1);
    cout << ans << '\n';

    return 0;
}
	


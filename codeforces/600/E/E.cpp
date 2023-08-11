#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, color[maxn];
vector<int> adj[maxn];
ll ans[maxn];

struct Node
{
    map<int,int>* mp;
    ll cursum;
    int maxOcc, id;
    inline int sz() { return mp->size(); }
    Node(int ii) {
        mp = new map<int,int>;
        cursum = 0;
        maxOcc = 0;
        id = ii;
    }
    void update(int c) {
        if ((*mp)[c] > maxOcc) {
            maxOcc = (*mp)[c];
            cursum = c;
        }
        else if ((*mp)[c] == maxOcc) {
            cursum += c;
        }
    }
    void addSelf() {
        (*mp)[color[id]]++;
        update(color[id]);
    }
};

void merge(Node& a, Node& b) {
    if (a.sz() < b.sz()) {
        swap(a,b);
        swap(a.id,b.id);
    }
    for (auto& p: (*b.mp)) {
        (*a.mp)[p.first] += p.second;
        a.update(p.first);
    }
}

Node* dfs(int i, int par) {
    Node* ni = new Node(i);
    for (int j: adj[i]) {
        if (j == par) continue;
        Node* nj = dfs(j,i);
        merge(*ni,*nj);
        delete nj;
    }
    ni->addSelf();
    ans[i] = ni->cursum;
    return ni;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //input
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,-1);
    //output
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? '\n' : ' ');
    }

    return 0;
}
	


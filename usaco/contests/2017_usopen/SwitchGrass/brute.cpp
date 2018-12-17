#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
template<class T>
struct Heap: public multiset<T>
{
    void add(T x) {
        this->insert(x);
    }
    void rem(T x) {
        auto it = this->find(x);
        if (it != this->end()) this->erase(it);
    }
    T getmin() {
        return *this->begin();
    }
};

void amin(int& a, int b) {
    a = min(a,b);
}

//dsu
int parent[maxn];
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

bool Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
    return true;
}

int N, M, K, Q;
int type[maxn];
struct Edge {
    int a, b, l;
    bool operator<(const Edge& r) const {
        return l < r.l;
    }
};

struct lEdge { //no shame
    int to, len;
};



struct Node
{
    lEdge parent, best1, best2;
    int color;
    Node() {
        parent = {0,0};
        best1 = {0,0};
        best2 = {0,0};
        color = 0;
    }
    Node(int c) {
        parent = {0,0};
        best1 = {0,0};
        best2 = {0,0};
        color = c;
    }
};
Node nodes[maxn];

vector<lEdge> adj[maxn]; //minimal spanning tree

void root(int i, int p) {
    nodes[i] = Node(type[i]);                    
    Node& ni = nodes[i];
    if (i == p) ni.parent = {0,0};
    map<int,lEdge> colorToMinEdge;
    for (const lEdge& e: adj[i]) {
        if (e.to == p) continue;
        root(e.to,i);
        Node& nj = nodes[e.to];
        nj.parent = {i,e.len};
        if (!colorToMinEdge.count(nj.color)) {
            colorToMinEdge[nj.color] = e;
        }
        else if (e.len < colorToMinEdge[nj.color].len) {
            colorToMinEdge[nj.color] = e;
        }
    }
    vector<lEdge> v;
    for (auto& p: colorToMinEdge) {
        v.emplace_back(p.second);
    }
    sort(v.begin(),v.end(),[](const lEdge& a, const lEdge& b) {
            return a.len < b.len;
            });
    if (v.size() >= 1) {
        ni.best1 = v[0];
    }
    if (v.size() >= 2) {
        ni.best2 = v[1];
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("grass.in","r",stdin); freopen("grass.out","w",stdout);
    cin >> N >> M >> K >> Q;
    memset(parent,-1,sizeof parent);
    vector<Edge> ee;
    for (int i = 0; i < M; i++) {
        int a, b, l; cin >> a >> b >> l;
        ee.push_back({a,b,l});
    }
    sort(ee.begin(),ee.end());
    vector<Edge> mstEdges;
    sort(ee.begin(),ee.end());
    for (const Edge& e: ee) {
        if (Union(e.a,e.b)) {
            mstEdges.emplace_back(e);
        }
    }
    sort(mstEdges.begin(),mstEdges.end());
    for (int i = 1; i <= N; i++) cin >> type[i];
    while (Q--) {
        int a, nc; cin >> a >> nc;
        type[a] = nc;
        for (Edge& e: ee) {
            if (type[e.a] != type[e.b]) {
                cout << e.l << '\n';
                break;
            }
        }
    }

    return 0;
}

//Idea: root mst
//At each node, keep track of parent edge, and two smallest edges with different colors
//

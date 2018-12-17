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
    bool active;
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

void activateEdge(int a, int b) {
    //active edge between a and b
    for (const lEdge& e: {nodes[a].parent,nodes[a].best1,nodes[a].best2}) {
        if (e.to == b) {
            if (!e.active) {
                
            }
            break;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("grass.in","r",stdin); freopen("grass.out","w",stdout);
    cin >> N >> M >> K >> Q;
    memset(parent,-1,sizeof parent);
    vector<Edge> ee;
    for (int i = 0; i < M; i++) {
        int a, b, l; cin >> a >> b >> l;
        ee.push_back({a,b,l});
    }
    for (int i = 1; i <= N; i++) cin >> type[i];
    vector<Edge> mstEdges;
    sort(ee.begin(),ee.end());
    for (const Edge& e: ee) {
        if (Union(e.a,e.b)) {
            adj[e.a].push_back({e.b,e.l});
            adj[e.b].push_back({e.a,e.l});
        }
    }
    root(1,1);
    /*
    for (int i = 1; i <= N; i++) {
        printf("%d: \nParent = %d, %d\nbest1 = %d, %d\nbest2 = %d, %d\n\n",i,nodes[i].parent.to,nodes[i].parent.len,nodes[i].best1.to,nodes[i].best1.len,nodes[i].best2.to,nodes[i].best2.len);
    }
    */
    Heap<int> heap;
    for (int i = 2; i <= N; i++) {
        if (nodes[i].color != nodes[nodes[i].parent.to].color) {
            heap.add(nodes[i].parent.len);
            //cout << i << " " << nodes[i].parent.to << ": " << nodes[i].parent.len << '\n';
        }
    }
    while (Q--) {
        int a, nc; cin >> a >> nc;
        int old = nodes[a].color;
        if (old != nc) {
            for (const lEdge& e: {nodes[a].parent,nodes[a].best1,nodes[a].best2}) {
                if (e.to == 0) continue; //ignore these
                Node ni = nodes[e.to];
                if (ni.color == old) {
                    //if it was same color, now add it to the heap
                    heap.add(e.len);
                }
                else if (ni.color == nc) {
                    //it's changed to same color, so delete it
                    heap.rem(e.len);    
                }
            }
        }
        nodes[a].color = nc;
        cout << heap.getmin() << '\n';
    }

    return 0;
}

//Idea: root mst
//At each node, keep track of parent edge, and two smallest edges with different colors
//

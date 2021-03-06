#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//implement DSU with rollbacks
//when rolling back change (a,b) (a is parent of b):
//a.szX -= b.szX, a.szY -= b.szY
//Reset b to be the parent of itself
//use random merging
const int maxn = 4e5;
int N, q;
ll ans[maxn+5];

struct Node //node in segment tree of queries
{
    int se, en;
    vector<pair<int,int>> edges;
    //edges that are present in this node
} nodes[4*maxn+5];

void build(int i, int se, int en) {
    nodes[i].se = se;
    nodes[i].en = en;
    if (se == en) return;
    int m = (se+en)>>1;
    build(i*2,se,m);
    build(i*2+1,m+1,en);
}

void addInterval(int i, int l, int r, const pair<int,int>& p) {
    if (l <= nodes[i].se && nodes[i].en <= r) {
        nodes[i].edges.push_back(p);
        return;
    }
    if (nodes[i].se == nodes[i].en) return;
    int mid = (nodes[i].se+nodes[i].en)/2;
    if (mid >= l) addInterval(i*2,l,r,p);
    if (mid < r) addInterval(i*2+1,l,r,p);
}

pair<int,int> qs[maxn+1];

vector<int> active;
//DSU information
int parent[2*maxn+10];
int sz[2*maxn+10];

int findParent(int i) {
    if (parent[i] == i) return i;
    return findParent(parent[i]);
}

void merge(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a,b);
    parent[b] = a;
    sz[a] += sz[b];
    active.push_back(b);
}

void rollback() {
    int b = active.back(); active.pop_back();
    int a = parent[b];
    parent[b] = b;
    sz[a] -= sz[b];
}

void DFS(int i) {
    int t0 = active.size();
    //cout << i << ": " << nodes[i].se << ' ' << nodes[i].en << endl;
    //add this interval's edges
    for (const auto& p: nodes[i].edges) {
        merge(p.first,p.second);
    }
    if (nodes[i].se == nodes[i].en) {
        if (qs[nodes[i].se] != make_pair(0,0)) {
            int x = findParent(qs[nodes[i].se].first);
            int y = findParent(qs[nodes[i].se].second);
            /*
            for (int j = 1; j <= N; j++) {
                cout << j << ": " << findParent(j) << '\n';
            }
            for (auto p: active) {
                cout << p << ' ' << parent[p] << '\n';
            }
            cout << nodes[i].se << ": " << qs[nodes[i].se].first << ' ' << qs[nodes[i].se].second << ": " << (x==y) << '\n';
            */
            ans[nodes[i].se] = (x==y);
        }
    }
    else {
        DFS(i*2);
        DFS(i*2+1);
    }
    //at the end, rollback edges
    while (active.size() > t0) {
        rollback();
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> q;
    map<pair<int,int>,int> curr;
    build(1,1,q);
    //pair<int,int> first;
    vector<int> queries;
    for (int i = 1; i <= q; i++) {
        string c; cin >> c;
        int x, y; cin >> x >> y;
        if (x > y) swap(x,y);
        if (c == "conn") {
            queries.push_back(i);
            qs[i] = {x,y};
        }
        else {
            pair<int,int> p = {x,y};
            if (c == "rem") {
                //add interval from [curr[{x,y}],i-1]
                //printf("[%d, %d]: (%d, %d)\n",curr[p],i-1,p.first,p.second);
                addInterval(1,curr[p],i-1,p);
                curr.erase(p);
            }
            else {
                assert(c == "add");
                curr[p] = i;
            }
        }
    }
    for (auto p: curr) {
        addInterval(1,p.second,q,p.first);
    }

    //initialize DSU
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    //DFS on segment tree
    DFS(1);
    //output
    for (int i: queries) {
        cout << (ans[i]?"YES":"NO") << '\n';
    }
}

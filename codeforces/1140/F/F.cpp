#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//implement DSU with rollbacks
//when rolling back change (a,b) (a is parent of b):
//a.szX -= b.szX, a.szY -= b.szY
//Reset b to be the parent of itself
//use random merging
const int maxn = 3e5;
int q;
pair<int,int> queries[maxn+5];
ll ans[maxn];

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

stack<int> active;
ll currAns = 0;
//DSU information
int parent[2*maxn+10];
pair<int,int> sz[2*maxn+10];

pair<int,int>& operator+=(pair<int,int>& a, pair<int,int> b) {
    a.first += b.first;
    a.second += b.second;
    return a;
}

pair<int,int>& operator-=(pair<int,int>& a, pair<int,int> b) {
    a.first -= b.first;
    a.second -= b.second;
    return a;
}

int findParent(int i) {
    if (parent[i] == i) return i;
    return findParent(parent[i]);
}

ll getCount(pair<int,int> p) {
    return 1LL*p.first*p.second;
}

void merge(int a, int b) {

    a = findParent(a);
    b = findParent(b);
    if (a == b) return;
    if (sz[a].first+sz[a].second<sz[b].first+sz[b].second) 
        swap(a,b);
    currAns -= getCount(sz[a]);
    currAns -= getCount(sz[b]);
    parent[b] = a;
    sz[a] += sz[b];
    currAns += getCount(sz[a]);
    active.push(b);
}

void addEdge(const pair<int,int>& p) {
    merge(p.first,p.second+maxn);
}

void rollback() {
    int b = active.top(); active.pop();
    int a = parent[b];
    //assert(p.first==a);
    currAns -= getCount(sz[a]);
    parent[b] = b;
    sz[a] -= sz[b];
    currAns += getCount(sz[a]);
    currAns += getCount(sz[b]);
}

void DFS(int i) {
    int t0 = active.size();
    //add this interval's edges
    for (const auto& p: nodes[i].edges) {
        addEdge(p);
    }
    if (nodes[i].se == nodes[i].en) {
        //cout << nodes[i].se << ": " << currAns << '\n';
        ans[nodes[i].se] = currAns;
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
    scanf("%d",&q);
    map<pair<int,int>,int> curr;
    build(1,1,q);
    //pair<int,int> first;
    for (int i = 1; i <= q; i++) {
        int x, y; scanf("%d %d",&x,&y);
        pair<int,int> p = {x,y};
        //if (i == 1) first = p;
        queries[i] = p;
        if (curr.count(p)) {
            //add interval from [curr[{x,y}],i-1]
            addInterval(1,curr[p],i-1,p);
            curr.erase(p);
        }
        else {
            curr[p] = i;
        }
    }
    for (auto p: curr) {
        addInterval(1,p.second,q,p.first);
    }
    /*
    for (int i = 1; i <= 4*q; i++) {
        printf("[%d, %d]:\n",nodes[i].se,nodes[i].en);
        for (auto p: nodes[i].edges) {
            cout << p.first << ' ' << p.second << '\n';
        }
    }
    */
    //initialize DSU
    for (int i = 1; i <= maxn; i++) {
        parent[i] = i;
        sz[i].first = 1;
    }
    for (int i = maxn+1; i <= 2*maxn; i++) {
        parent[i] = i;
        sz[i].second = 1;
    }
    //DFS on segment tree
    DFS(1);
    //output
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << " \n"[i==q];
    }
}


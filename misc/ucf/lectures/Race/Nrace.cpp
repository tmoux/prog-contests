#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 200005;
const int INF = 999999999;
int n, k;
int ans = 0;
struct Edge {
    int other, weight;    
};
vector<Edge> adj[maxn];

struct Node
{
    map<int,int>* mp;
    int lAux, pathAux;
    int curr;
    inline int sz() {return mp->size();}
    Node() {
        mp = new map<int,int>;
        pathAux = 0;
        lAux = 0;
        curr = INF;
    }
    void addSelf() {
        (*mp)[-lAux] = -pathAux;
    }
    
} nodes[maxn];

void merge(Node& a, Node& b, int weight) {
    b.lAux += weight;
    bool swapped = false;
    if (a.sz() < b.sz()) {
        swap(a,b);
        swapped = true;
    }
    //check for paths
    if (!swapped) {
        if (a.mp->count(k-weight-a.lAux)) {
            int n2 = (*a.mp)[k-weight-a.lAux] + a.pathAux;
            ans = min(ans,1+n2);
        }
    }
    for (auto p: (*b.mp)) {
        int len = p.first + b.lAux;
        int num = p.second + b.pathAux;
        if (a.mp->count(k-len-a.lAux)) {
            int n2 = (*a.mp)[k-len-a.lAux] + a.pathAux;
            ans = min(ans,num+n2);
        }
    }
    //now add the paths
    for (auto p: (*b.mp)) {
        int len = p.first + b.lAux;
        int num = p.second + b.pathAux;
        if (!a.mp->count(len-a.lAux)) {
            (*a.mp)[len-a.lAux] = num-a.pathAux;    
        }
        else if ((*a.mp)[len-a.lAux] > num-a.pathAux) {
            (*a.mp)[len-a.lAux] = num-a.pathAux;
        }
    }
    //add the path from a to b itself
    if (!swapped) {
        if (!a.mp->count(weight-a.lAux)) {
            (*a.mp)[weight-a.lAux] = 1 - a.pathAux;
        }
        else if ((*a.mp)[weight-a.lAux] > weight-a.pathAux) {
            (*a.mp)[weight-a.lAux] = 1 - a.pathAux;
        }
    }
    delete b.mp;
}

void dfs(int i, int par) {
    nodes[i] = Node();
    nodes[i].addSelf();
    for (Edge e: adj[i]) {
        if (e.other == par) continue;
        dfs(e.other,i);
        merge(nodes[i],nodes[e.other],e.weight);
    }
    nodes[i].pathAux++;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int h1, h2, li; cin >> h1 >> h2 >> li;
        adj[h1].push_back({h2,li});
        adj[h2].push_back({h1,li});
    }
    ans = INF;
    dfs(0,-1);
    cout << (ans == INF ? -1 : ans) << '\n';
    return 0;
}
	


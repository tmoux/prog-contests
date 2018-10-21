#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, m;
int parent[maxn];

struct Edge
{
    int u, v, weight;
    bool operator<(const Edge& rhs) const {
        return weight < rhs.weight;
    }
};

int Find(int node) {return parent[node] < 0 ? node : (parent[node] = Find(parent[node]));}

void Union(int x, int y) 
{
	x = Find(x);
	y = Find(y);
	if (x == y) return;
	if (parent[x] > parent[y]) {
		swap(x,y);
	}
	parent[x] += parent[y];
	parent[y] = x;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
    }
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, t; cin >> u >> v >> t;
        edges[i] = {u,v,t};
    }
    ll totalcost = 0;
    sort(edges.begin(),edges.end());
    for (Edge e: edges) {
        if (Find(e.u) != (Find(e.v))) {
            totalcost += (ll)e.weight;
            Union(e.u,e.v);
        }
    }
    cout << totalcost << '\n';


    return 0;
}
	


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5, INF = 2e9;
int N, K;
struct Edge { int nx, weight; };
vector<Edge> adj[maxn];
bool blocked[maxn];
int subtreeSize[maxn];

int dfsSize(int i, int par) {
    subtreeSize[i] = 1;
    for (Edge e: adj[i]) {
        if (!blocked[e.nx] && e.nx != par) {
            subtreeSize[i] += dfsSize(e.nx,i); 
        }
    }
    return subtreeSize[i];
}

int findCentroid(int i, int par, int compSize) {
    for (Edge e: adj[i]) {
        if (!blocked[e.nx] && e.nx != par) {
            if (subtreeSize[e.nx] * 2 > compSize) {
                return findCentroid(e.nx,i,compSize);
            }
        }
    }
    return i;
}

struct Path { int weight, length; } paths[maxn];
void fillDfs(int i, int par, map<int,int>& adding) {
    if (paths[i].weight > K) return;
    if (adding.count(paths[i].weight)) {
        adding[paths[i].weight] = min(adding[paths[i].weight],paths[i].length);
    }
    else {
        adding[paths[i].weight] = paths[i].length;
    }
    for (Edge e: adj[i]) {
        if (!blocked[e.nx] && e.nx != par) {
            paths[e.nx] = {paths[i].weight + e.weight, paths[i].length + 1};
            fillDfs(e.nx,i,adding);
        }
    }
}

int solveTree(int centroid) {
    map<int,int> minLenforWeight;
    minLenforWeight[0] = 0;
    int ans = INF;
    for (Edge e: adj[centroid]) {
        if (!blocked[e.nx]) {
            map<int,int> adding;
            paths[e.nx] = {e.weight,1};
            fillDfs(e.nx,centroid,adding);
            for (auto p: adding) {
                if (minLenforWeight.count(K-p.first)) {
                    ans = min(ans,p.second+minLenforWeight[K-p.first]);
                }
            }
            for (auto p: adding) {
                if (minLenforWeight.count(p.first)) {
                    minLenforWeight[p.first] = min(minLenforWeight[p.first],p.second);
                }
                else {
                    minLenforWeight[p.first] = p.second;
                }
            }
        }
    }
    return ans;
}

int decomp(int i) {
    int compSize = dfsSize(i,i);
    int centroid = findCentroid(i,i,compSize);
    int ans = solveTree(centroid);
    
    blocked[centroid] = true;
    for (Edge e: adj[centroid]) {
        if (!blocked[e.nx]) {
            ans = min(ans,decomp(e.nx));
        }
    }
    
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    int ans = decomp(0);
    cout << (ans == INF ? -1 : ans) << '\n';

    return 0;
}
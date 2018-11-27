#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5, M = 1e9+7;
int N, K;
vector<int> adj[maxn];
bool blocked[maxn];
int subtreeSize[maxn];

int dfsSize(int i, int par) {
    subtreeSize[i] = 1;
    for (int j: adj[i]) {
        if (!blocked[j] && j != par) {
            subtreeSize[i] += dfsSize(j,i); 
        }
    }
    return subtreeSize[i];
}

int findCentroid(int i, int par, int compSize) {
    for (int j: adj[i]) {
        if (!blocked[j] && j != par) {
            if (subtreeSize[j] * 2 > compSize) {
                return findCentroid(j,i,compSize);
            }
        }
    }
    return i;
}

void fillDfs(int i, int par, int depth, map<int,int>& adding) {
    adding[depth]++;
    for (int j: adj[i]) {
        if (!blocked[j] && j != par) {
            fillDfs(j,i,depth+1,adding);
        }
    }
}

ll solveTree(int centroid) {
    map<int,int> curr;
    curr[0] = 1;
    ll ans = 0;
    for (int j: adj[centroid]) {
        if (blocked[j]) continue;
        map<int,int> mp;
        fillDfs(j,centroid,1,mp);
        for (auto p: mp) {
            if (curr.count(K-p.first)) {
                ans = (ans + (ll)p.second * (curr[K-p.first])) % M;    
            }
        }
        for (auto p: mp) {
            curr[p.first] += p.second;
        }
    }
    return ans;
}

ll decomp(int i) {
    int compSize = dfsSize(i,i);
    int centroid = findCentroid(i,i,compSize);
    ll ans = solveTree(centroid);
    
    blocked[centroid] = true;
    for (int j: adj[centroid]) {
        if (!blocked[j]) {
            ans = (ans + decomp(j)) % M;
        }
    }
    
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifndef OFFLINE
    freopen("in","r",stdin);
    #endif
    cin >> N >> K;
    for (int i = 0; i < N - 1; i++) {
        int u, v, w; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll ans = decomp(1);
    cout << (((ll)(K+1)*K/2)%M * ans) % M << '\n';

    return 0;
}

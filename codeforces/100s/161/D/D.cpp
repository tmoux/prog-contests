#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e4+5;
int N, K;
vector<int> adj[maxn];
bool blocked[maxn];
int treeSize[maxn];

int dfsSize(int i, int par) {
    treeSize[i] = 1;
    for (int j: adj[i]) {
        if (!blocked[j] && j != par) {
            treeSize[i] += dfsSize(j,i);
        }
    }
    return treeSize[i];
}

int getCentroid(int i, int par, int compSize) {
    for (int j: adj[i]) {
        if (!blocked[j] && j != par) {
            if (treeSize[j] * 2 > compSize) {
                return getCentroid(j,i,compSize);
            }
        }
    }
    return i;
}

void solvedfs(int i, int par, map<int,int>& adding, int depth) {
    adding[depth]++;
    for (int j: adj[i]) {
        if (!blocked[j] && j != par) {
            solvedfs(j,i,adding,depth+1);
        }
    }
}

ll solveTree(int centroid) {
    map<int,int> orig;
    orig[0] = 1;
    ll res = 0;
    for (int j: adj[centroid]) {
        if (!blocked[j]) {
            map<int,int> adding;
            solvedfs(j,centroid,adding,1);
            for (auto& p: adding) {
                if (orig.count(K-p.first)) {
                    res += 1LL*p.second*orig[K-p.first];
                }
            }
            //merge
            for (auto& p: adding) {
                orig[p.first] += p.second;
            }
        }
    }
    return res;
}

ll decomp(int i) {
    int compSize = dfsSize(i,i);
    int centroid = getCentroid(i,i,compSize);
    blocked[centroid] = true;
    //cout << centroid << '\n';
    ll ans = solveTree(centroid);
    //cout << centroid << ' ' << ans << '\n';
    for (int j: adj[centroid]) {
        if (!blocked[j]) {
            ans += decomp(j);
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << decomp(1) << '\n';

    return 0;
}
	


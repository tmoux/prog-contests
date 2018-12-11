#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, k;
vector<int> adj[maxn];
char letter[maxn];
bool blocked[maxn];
int sub_size[maxn];

int dfs_size(int i, int p) {
    sub_size[i] = 1;
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        sub_size[i] += dfs_size(j,i);
    }
    return sub_size[i];
}

int getCentroid(int i, int p, int compSize) {
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        if (sub_size[j] * 2 >= compSize) return getCentroid(j,i,compSize);
    }
    return i;
}

int getDepth(int i, int p) {
    int r = 1;
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        r = max(r,getDepth(j,i)+1);    
    }
    return r;
}

void fillPaths(int i, int p, int depth, ll* adding, int& maxd) {
    maxd = max(maxd,depth);
    adding[depth]++;
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        fillPaths(j,i,depth+1,adding,maxd);
    }
}

ll paths[maxn], adding[maxn];

ll solveTree(int centroid) {
    ll res = 0;
    int depth = getDepth(centroid,centroid);    
    for (int i = 0; i <= depth; i++) { 
        paths[i] = 1;
        adding[i] = 0;
    }
    paths[0] = 1;
    for (int j: adj[centroid]) {
        if (blocked[j]) continue;
        //memset(adding,0,sizeof(ll)*depth);
        int maxd = 0;
        fillPaths(j,centroid,1,adding,maxd);    
        /*
        cout << "centroid= " << centroid << ", " << j << '\n';
        for (int j = 1; j <= maxd; j++) {
            cout << j << ": " << adding[j] << '\n';
        }
        cout << '\n';
        */
        for (int a = 1; a <= min(k,maxd); a++) {
            res += 1LL * adding[a] * paths[max(0,k-a)];    
            adding[a] += adding[a-1];
        }
        for (int a = 1; a <= maxd; a++) {
            paths[a] += adding[a];
            adding[a] = 0;
        }
    }

    return res;
}

ll decomp(int i) {
    int compSize = dfs_size(i,i);
    int centroid = getCentroid(i,i,compSize);
    blocked[centroid] = true;
    ll ans = solveTree(centroid);
    //cout << "centroid= " << centroid << '\n';
    for (int j: adj[centroid]) {
        if (blocked[j]) continue;
        ans += decomp(j);
    }
    cout << centroid << ": " << ans << '\n';
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> letter[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        if (letter[u] != letter[v]) continue;
        adj[u].push_back(v);
        adj[v].push_back(u);
        //cout << u << ' ' << v << '\n';
    }
    ll ans = 0LL;
    for (int i = 1; i <= n; i++) {
        if (!blocked[i]) {
            //cout << "starting = " << i << '\n';
            ans += decomp(i);
        }
    }
    cout << ans << '\n';
    return 0;
}
	


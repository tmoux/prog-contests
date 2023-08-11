#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxk = 21;
int n, A[maxn];
vector<int> adj[maxn];
int sub_size[maxn];
bool vis[maxn];

int dfs_size(int i, int par) {
    sub_size[i] = 1;
    for (int j: adj[i]) {
        if (j != par && !vis[j]) {
            sub_size[i] += dfs_size(j,i);
        }
    }
    return sub_size[i];
}

int get_centroid(int i, int par, int compSize) {
    for (int j: adj[i]) {
        if (j != par && !vis[j]) {
            if (sub_size[j] * 2 > compSize) {
                return get_centroid(j,i,compSize);
            }
        }
    }
    return i;
}

inline void accum_array(int add, ll cnt[maxk][2]) {
    for (int i = 0; i < maxk; i++) {
        bool as = add & (1 << i);
        cnt[i][as]++;
    }
}

inline ll getans(int add, ll cnt[maxk][2]) {
    ll res = 0;
    for (int i = 0; i < maxk; i++) {
        bool as = add & (1 << i);
        res += (1LL << i) * cnt[i][as^1];
    }
    return res;
}

void solve_dfs(int i, int par, vector<int>& adding,int curr) {
    adding.push_back(A[i] ^ curr);
    for (int j: adj[i]) {
        if (j != par && !vis[j]) {
            solve_dfs(j,i,adding,curr^A[i]);
        }
    }
}

ll solve_tree(int centroid) {
    ll cnt[maxk][2]; memset(cnt,0,sizeof(cnt));
    accum_array(A[centroid],cnt);
    ll res = A[centroid];
    for (int j: adj[centroid]) {
        if (!vis[j]) {
            vector<int> adding;
            solve_dfs(j,centroid,adding,0);

            for (int add: adding) {
                res += getans(add,cnt);
            }
            for (int add: adding) {
                accum_array(add^A[centroid],cnt);
            }
        }
    }
    return res;
}
    
ll get_decomp(int i) {
    int compSize = dfs_size(i,i);
    int centroid = get_centroid(i,i,compSize);
    vis[centroid] = true;
    ll res = solve_tree(centroid);
    for (int j: adj[centroid]) {
        if (!vis[j]) {
            res += get_decomp(j);
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll res = get_decomp(1);
    cout << res << '\n';

    return 0;
}
	



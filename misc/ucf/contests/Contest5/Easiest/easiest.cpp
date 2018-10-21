#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, k, sub_size[maxn];
vector<int> adj[maxn];
char label[maxn];
bool vis[maxn];

int dfs_size(int i, int par) {
    sub_size[i] = 1;
    for (int j: adj[i]) {
        if (j == par || vis[j]) continue;
        sub_size[i] += dfs_size(j,i);
    }
    return sub_size[i];
}

int get_centroid(int i, int par, int compSize) {
    for (int j: adj[i]) {
        if (j == par || vis[j]) continue;
        if (sub_size[j] * 2 > sub_size[i]) {
            return get_centroid(j,i,compSize);
        }
    }
    return i;
}

int fen[maxn], adding[maxn];
   
void add(int idx, int val, int A[], int n) {
    n++;
    idx++;
    while (idx <= n) {
        A[idx] += val;
        idx += idx & (-idx);
    }
}
ll query(int idx, int A[]) {
    idx++;
    ll sum = 0LL;
    while (idx > 0) {
        sum += A[idx];
        idx -= idx & (-idx);
    }
    return sum;
}

ll getsum(int l, int r, int A[]) {
    return query(r,A) - query(l-1,A);
}

void dfs_solve(int i, int par, int dep, int A[], int compSize) {
    add(dep,1,A,n);
    for (int j: adj[i]) {
        if (vis[j] || j == par) continue;
        dfs_solve(j,i,dep+1,A,compSize);
    }
}

ll solve_tree(int centroid, int compSize) {
    ll res = 0;
    memset(fen,0,sizeof(int)*(compSize+2));
    add(0,1,fen,n);
    for (int j: adj[centroid]) {
        if (!vis[j]) {
            memset(adding,0,sizeof(int)*(compSize+2));     
            dfs_solve(j,centroid,1,adding,compSize);
            for (int i = 1; i <= compSize; i++) {
                int num = getsum(i,i,adding);
                if (num == 0 || i > k) break;
                int x = query(k-i,fen);
                res += 1LL*x*num;
            }

            for (int i = 1; i <= compSize; i++) {
                int num = getsum(i,i,adding);
                if (num == 0 || i > k) break;
                add(i,num,fen,n);
            }
        }
    }
    return res;
}

ll decomp(int i) {
    int compSize = dfs_size(i,i);
    int centroid = get_centroid(i,i,compSize);
    vis[centroid] = true;
    ll res = solve_tree(centroid,compSize);
    for (int j: adj[centroid]) {
        if (!vis[j]) {
            res += decomp(j);
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> label[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        if (label[u] == label[v]) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    //get answer
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            ans += decomp(i);
        }
    }
    cout << ans << '\n';

    return 0;
}
	


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
int sub_size[maxn], label[maxn];
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
    
void get_decomp(int i, int lab) {
    assert(lab < 26);
    int compSize = dfs_size(i,i);
    int centroid = get_centroid(i,i,compSize);
    vis[centroid] = true;
    label[centroid] = lab;
    for (int j: adj[centroid]) {
        if (!vis[j]) {
            get_decomp(j,lab+1);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    get_decomp(1,0);
    for (int i = 1; i <= n; i++) {
        cout << (char)(label[i] + 'A') << ' ';
    }

    return 0;
}
	


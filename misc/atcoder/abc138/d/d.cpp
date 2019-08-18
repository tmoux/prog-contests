#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int N, Q;
vector<int> adj[maxn];
int pre[maxn];
int tin[maxn], tout[maxn], t = 0;

void dfs(int i, int p) {
    tin[i] = t++;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
    tout[i] = t;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for (int i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    for (int i = 0; i < Q; i++) {
        int p, x; cin >> p >> x;
        pre[tin[p]] += x;
        pre[tout[p]] -= x;
    }
    for (int i = 1; i <= N; i++) {
        pre[i] += pre[i-1];
    }
    for (int i = 1; i <= N; i++) {
        cout << pre[tin[i]] << ' ';
    }
    cout << '\n';
}


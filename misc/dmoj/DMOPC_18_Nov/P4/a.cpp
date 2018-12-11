#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int N, K;
struct Edge
{
    int to, weight;
};
vector<Edge> adj[maxn];
int cnt[maxn];
int sub_size[maxn];

int dfs(int i, int p) {
    sub_size[i] = cnt[i];
    for (Edge e: adj[i]) {
        if (e.to == p) continue;
        sub_size[i] += dfs(e.to,i);        
    }
    return sub_size[i];
}

int getCentroid(int i, int p) {
    for (Edge e: adj[i]) {
        if (e.to == p) continue;
        if (sub_size[e.to]*2 >= K) return getCentroid(e.to,i);
    }
    return i;
}

ll ans = 0;

void dfs2(int i, int p, int d) {
    ans += 1LL*cnt[i]*d;
    for (Edge e: adj[i]) {
        if (e.to == p) continue;
        dfs2(e.to,i,d+e.weight);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> K >> N;
    for (int i = 0; i < K; i++) {
        int zi; cin >> zi;
        cnt[zi]++;
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b, d; cin >> a >> b >> d;
        adj[a].push_back({b,d});
        adj[b].push_back({a,d});
    }
    dfs(1,1);
    int centroid = getCentroid(1,1);
    dfs2(centroid,centroid,0);
    cout << ans << '\n';

    return 0;
}


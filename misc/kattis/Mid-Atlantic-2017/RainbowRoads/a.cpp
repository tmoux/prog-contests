#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e4+5;
int n, ccount[maxn], val[maxn];
struct Edge { int to, color; };
vector<Edge> adj[maxn];

void dfs(int i, int p) {
    for (Edge& e: adj[i]) {
        ccount[e.color]++;
    }
    for (Edge e: adj[i]) {
        if (e.to == p && ccount[e.color] > 1) {
            val[1]++;
            val[i]--;
        }
        else if (e.to != p && ccount[e.color] > 1) {
            val[e.to]++;
        }
    }
    for (Edge& e: adj[i]) {
        ccount[e.color]--;
    }
    for (Edge& e: adj[i]) {
        if (e.to == p) continue;
        dfs(e.to,i);
    }
}

void dfs2(int i, int p) {
    for (Edge& e: adj[i]) {
        if (e.to == p) continue;
        val[e.to] += val[i];
        dfs2(e.to,i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    dfs(1,1);
    dfs2(1,1);
    vector<int> ans;
    for (int i = 1; i <= n; i++)
        if (val[i] == 0) ans.push_back(i);
    //output
    cout << ans.size() << '\n';
    for (int i: ans) cout << i << '\n';

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
struct Edge
{
    int to, w;
};
vector<Edge> adj[maxn];

ll f(int i, int p) {
    vector<int> weights;
    ll ans = 0;
    for (Edge e: adj[i]) {
        if (e.to == p) continue;
        else {
            weights.push_back(e.w);
            ans += f(e.to,i);
        }
    }
    if (!weights.empty()) {
        sort(weights.begin(),weights.end(),greater<int>());
        for (int i = 0; i < weights.size(); i++) {
            ans += 2*weights[i];
        }
    }
    return ans;
}

ll longest[maxn];

void dfs(int i, int p) {
    for (Edge e: adj[i]) {
        if (e.to == p) continue;
        dfs(e.to,i);
        longest[i] = max(longest[i],e.w+longest[e.to]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b, w; cin >> a >> b >> w;
        adj[a].push_back({b,w});
        adj[b].push_back({a,w});
    }
    ll ans = f(1,1);
    dfs(1,1);    
    ans -= longest[1];
    cout << ans << '\n';
}


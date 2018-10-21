#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;

const int maxn = 2005;
const ll INF = 10000000000000000;
int n, m;
int weight[maxn][maxn];

ll dist() {
    ll d[maxn];    
    for (int i = 1; i <= n; i++) {
        d[i] = INF;
    }
    d[1] = 0LL;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int f = q.front();
        for (int i = 1; i <= n; i++) {
            if (weight[f][i] == 0) continue;
            if (weight[f][i] + d[f] < d[i]) {
                d[i] = (ll)weight[f][i] + d[f];
                q.push(i);
            }
        }
        q.pop();
    }
    return d[n];
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; i++) {  
        int u, v, t; cin >> u >> v >> t;
        weight[u][v] = t;
        weight[v][u] = t;
        edges[i] = {u,v};
    }
    ll ans1 = dist();
    for (int i = 0; i < m; i++) {
        int u = edges[i].first, v = edges[i].second;
        int ci; cin >> ci;
        weight[u][v] += ci;
        weight[v][u] += ci;
    }
    ll ans2 = dist();
    cout << (ans2-ans1) << '\n';


    return 0;
}
	


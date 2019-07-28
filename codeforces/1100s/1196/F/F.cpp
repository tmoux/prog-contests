#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m, k; 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct Edge
{
    int u, v, wt;
};

ll INF = 1e18;
//gp_hash_table<int,gp_hash_table<int,ll>> dist;
//map<int,map<int,ll>> dist;
ll dist[805][805];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int x, y, w; cin >> x >> y >> w;
        edges.push_back({x,y,w});
    }
    sort(edges.begin(),edges.end(),[](auto a, auto b) {
                return a.wt < b.wt; });
    //400 >= k > m >= n-1
    vector<int> vertices;
    for (int i = 0; i < min(m,k); i++) {
        vertices.push_back(edges[i].u);                
        vertices.push_back(edges[i].v);                
    }
    sort(vertices.begin(),vertices.end());
    vertices.erase(unique(vertices.begin(),vertices.end()),vertices.end());
    int pt = 1;
    map<int,int> mp;
    for (int& i: vertices) {
        mp[i] = pt++;
        i = mp[i];
    }
    for (int i = 1; i < pt; i++) {
        for (int j = 1; j < pt; j++) {
            dist[i][j] = INF;
        }
    }
    for (auto e: edges) {
        dist[mp[e.u]][mp[e.v]] = e.wt;
        dist[mp[e.v]][mp[e.u]] = e.wt;
    }
    for (int i = 1; i < pt; i++) {
        dist[i][i] = 0;
    }
    for (int k = 1; k < pt; k++) {
        for (int i = 1; i < pt; i++) {
            for (int j = 1; j < pt; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    vector<ll> ans;
    for (int i = 1; i < pt; i++) {
        for (int j = i+1; j < pt; j++) {
            ans.push_back(dist[i][j]);
        }
    }
    //nth_element(ans.begin(),ans.begin()+k,ans.end());
    sort(ans.begin(),ans.end());
    /*
    for (int i: ans) {
        cout << i << '\n';
    }
    */
    cout << ans[k-1] << '\n';
}


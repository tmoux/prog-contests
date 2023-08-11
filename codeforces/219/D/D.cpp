#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

struct Edge
{
    int nx;
    bool isUp;
};

const int maxn = 200005;
int n;
vector<Edge> adj[maxn];
int uppath[maxn];
int dist[maxn];
int totalup[maxn];

void dfs(int i, int par, int d) {
    dist[i] = d;
    for (Edge e: adj[i]) {
        if (e.nx == par) {
            uppath[i] = uppath[e.nx] + !e.isUp;
        }
    }
    for (Edge e: adj[i]) {
        if (e.nx == par) continue;
        dfs(e.nx,i,d+1);
        totalup[i] += totalup[e.nx] + e.isUp;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int si, ti; cin >> si >> ti;
        adj[si].push_back({ti,0});
        adj[ti].push_back({si,1});
    }
    uppath[1] = 0;
    dfs(1,0,0);
    //output
    int ans = n;
    vector<int> res;
    //cout << totalup[1] << '\n';
    for (int i = 1; i <= n; i++) {
        //cout << i << ' ' << uppath[i] << ' ' << dist[i] << '\n';    
        int fi = totalup[1] + dist[i] - 2*uppath[i];
        if (fi < ans) {
            ans = fi;
            res = {i};
        }
        else if (fi == ans) {
            res.push_back(i);
        }
    }

    cout << ans << '\n';
    for (int i: res) {
        cout << i << ' ';
    }
    
    
    return 0;
}
	


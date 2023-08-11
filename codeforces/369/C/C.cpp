#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Edge
{
    int x, y, t;
};

const int maxn = 100005;
int n;
vector<Edge> adj[maxn];
int ans[maxn];
vector<int> adds;

void dfs1(int i, const Edge& pre={0,0,0}) {
    for (Edge e: adj[i]) {
        if (e.y != pre.x) {
            dfs1(e.y,e);
            ans[i] += ans[e.y];
        }
    }

    if (ans[i] == 0 && pre.t == 2) {
        ans[i]++;
        adds.push_back(i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y, t; cin >> x >> y >> t;
        adj[x].push_back({x,y,t});
        adj[y].push_back({y,x,t});
    }

    dfs1(1);
    cout << ans[1] << '\n';
    for (int i: adds) {
        cout << i << ' ';
    }
    

    return 0;
}
	


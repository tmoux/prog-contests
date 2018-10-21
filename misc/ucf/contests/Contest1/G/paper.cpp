#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, m, k;
vector<int> adj[maxn];

int dist[maxn];
int mindist[maxn];
bool seen[maxn];

struct State
{
    int i, dist, cost;
};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    vector<State> starts;
    for (int i = 1; i <= k; i++) {
        int c; cin >> c;
        starts.push_back({i,0,c});
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        mindist[i] = 2000000000;
    }

    for (State s: starts) {
        memset(seen,0,sizeof(seen));
        queue<State> q;
        q.push(s);
        while (!q.empty()) {
            State f = q.front();
            seen[f.i] = true;
            dist[f.i] = f.dist;
            for (int j: adj[f.i]) {
                if (!seen[j]) {
                    seen[j] = true;
                    q.push({j,f.dist + f.cost, f.cost});
                }
            }
            q.pop();
        }

        for (int i = 1; i <= n; i++) {
            mindist[i] = min(mindist[i], dist[i]);
        }

    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += mindist[i];
        //cout << i << ' ' << mindist[i] << '\n';
    }
    cout << ans << '\n';



    return 0;
}
	


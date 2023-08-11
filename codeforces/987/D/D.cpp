#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;

//for each node i, calculate the cost of bringing each good k to i. then takeminimum s.
const int maxn = 100005;
const int maxk = 105;
int n, m, k, s;
vector<int> adj[maxn];
int closest[maxn][maxk]; //min cost of bringing good k to node n
int gd[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k >> s;
    for (int i = 1; i <= n; i++) {
        cin >> gd[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    //breadth first searches
    memset(closest,-1,sizeof(closest));
    for (int i = 1; i <= k; i++) {
        queue<int> q;
        for (int j = 1; j <= n; j++) {
            if (gd[j] == i) {
                q.push(j);
                closest[j][i] = 0;
            }   
        }

        while (!q.empty()) {
            int f = q.front();
            for (int nx: adj[f]) {
                if (closest[nx][i] == -1 || (closest[f][i] + 1 < closest[nx][i])) {
                    closest[nx][i] = closest[f][i] + 1;
                    q.push(nx);
                }
            }
            q.pop();
        }
    }
/*
    for (int a = 1; a <= k; a++) {
        cout << a << ' ';
        for (int i = 1; i <= n; i++) {
            cout << closest[i][a] << ' ';
        }
        cout << '\n';
    }
*/

    for (int i = 1; i <= n; i++) {
        vector<int> mins;
        for (int j = 1; j <= k; j++) {
            mins.push_back(closest[i][j]);
        }
        sort(mins.begin(),mins.end());
        int ans = 0;
        for (int a = 0; a < s; a++) {
            ans += mins[a];
        }
        cout << ans << ' ';
    }
    return 0;
}
	


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n;
bool color[maxn];
vector<int> adj[maxn];

void dfs(int i, int par, int& t) {
    for (int j: adj[i]) {
        if (j == par) continue;
        if (!color[i] && color[j]) {
            t++;
            cout << i << ' ' << j << '\n';
        }
        dfs(j,i,t);
    }
}

void startdfs(int& t) {
    if (color[1]) t++;
    dfs(1,-1,t);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int total1 = 0, total2 = 0;
    //startdfs(total1);
    for (int i = 1; i <= n; i++) {
        color[i] ^= 1;
    }
    startdfs(total2);
    cout << total1 << ' ' << total2 << '\n';

    return 0;
}
	


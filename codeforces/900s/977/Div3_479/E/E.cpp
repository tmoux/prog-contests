#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
vector<int> adj[maxn];
bool visited[maxn];
int n, m;

void dfs(int i, bool& canWork) {
    visited[i] = true;
    canWork &= (adj[i].size() == 2);
    for (int j: adj[i]) {
        if (!visited[j]) {
            dfs(j,canWork);
        }
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int vi, ui; cin >> vi >> ui;
        adj[vi].push_back(ui);
        adj[ui].push_back(vi);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            bool canWork = (adj[i].size() == 2);
            dfs(i,canWork);
            if (canWork) {
                ans++;
            }
        }
    }
    cout << ans << '\n';


    return 0;
}
	


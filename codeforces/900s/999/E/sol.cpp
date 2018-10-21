#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 5005;
vector<int> adj[maxn];
bool seen[maxn], used[maxn];
int parents[maxn];
int n, m, s;

void dfs(int i) {
    seen[i] = true;
    for (int j: adj[i]) {
        if (!seen[j]) {
            dfs(j);
        }
    }
}

void dfs2(int i, int& count) {
    used[i] = true;
    count++;
    for (int j: adj[i]) {
        if (!seen[j] && !used[j]) {
            dfs2(j,count);
        }
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        parents[v]++;
    }
    dfs(s);
    int ans = 0;
    vector<pair<int,int>> vec;
    for (int i = 1; i <= n; i++) {
        if (!seen[i]) {
            memset(used,false,sizeof(used));
            int count = 0;
            dfs2(i,count);
            vec.push_back({count,i});
        }
    }
    sort(vec.begin(),vec.end());
    for (int i = vec.size() - 1; i >= 0; i--) {
        if (!seen[vec[i].second]) {
            dfs(vec[i].second);
            ans++;
        }
    }
    cout << ans << '\n';


    return 0;
}
	


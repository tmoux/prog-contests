#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, s;
vector<int> adj[maxn];
int center;

bool check(double m) {
        
}

int indegree[maxn];
int depth[maxn], cnt[maxn];

void dfs(int i, int p) {
    depth[i] = depth[p] + 1;
    if (i == center) depth[i]--;
    cnt[depth[i]]++;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);    
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        indegree[a]++;
        indegree[b]++;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) if (indegree[i] <= 1) cnt++;
    double ans = (double)(s)/cnt*2;
    cout << fixed << setprecision(10) << ans << '\n';
    
    
    return 0;
}


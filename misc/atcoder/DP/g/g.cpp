#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, M;
vector<int> adj[maxn];
int indegree[maxn];

vector<int> topsort() {
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    vector<int> res;
    while (!q.empty()) {
        int f = q.front(); q.pop();
        res.push_back(f);
        for (int j: adj[f]) {
            indegree[j]--;
            if (indegree[j] == 0) q.push(j);
        }
    }
    return res;
}

int dp[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        indegree[b]++;
    }
    //topsort
    vector<int> t = topsort();
    int ans = 0;
    while (!t.empty()) {
        int f = t.back();
        t.pop_back();
        for (int j: adj[f]) {
            dp[f] = max(dp[f],1+dp[j]);
        }
        ans = max(ans,dp[f]);
    }
    cout << ans << '\n';

    return 0;
}


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int N, K;
struct Edge
{
    int to, weight;
    bool isSuper;
};
vector<Edge> adj[maxn];

int super[maxn];
int dp[maxn];

void fillSuper(int i, int p) {
    for (Edge& e: adj[i]) {
        if (e.to == p) continue;
        fillSuper(e.to,i);
        if (!e.isSuper) continue;
        super[i] += super[e.to] + e.weight;
    }
    //cout << "super " << i << ": " << super[i] << '\n';
}

int ans = 0;
void dfs(int i, int p) {
    dp[i] = 2*super[i];
    vector<int> vec;
    for (Edge& e: adj[i]) {
        if (e.to == p) continue;
        dfs(e.to,i);
        int r = dp[e.to] + e.weight;
        if (e.isSuper) r -= 2*(super[e.to] + e.weight);
        dp[i] = max(dp[i],2*super[i] + r);
        vec.push_back(r);
    }
    //cout << i << ": " << dp[i] << '\n';
    sort(vec.begin(),vec.end(),greater<int>());
    if (vec.size() < 2) {
        vec.push_back(0);
        vec.push_back(0);
    }
    ans = max(ans,dp[i]+vec[1]);
    /*
    ans = max(ans,dp[i][0]+dp[i][1]+2*super[i]);
    for (int& a: dp[i]) {
        a += 2*super[i];
    }
    */
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    vector<int> ks(K);
    for (int i = 0; i < K; i++) {
        cin >> ks[i];    
    }
    sort(ks.begin(),ks.end(),greater<int>());
    for (int i = 0; i < N - 1; i++) {
        int a, b, t; cin >> a >> b >> t;
        bool is = false;
        if (!ks.empty() && i+1 == ks.back()) {
            is = true;
            ks.pop_back();
        }
        adj[a].push_back({b,t,is});
        adj[b].push_back({a,t,is});
    }
    fillSuper(1,1);
    dfs(1,1);
    cout << ans << '\n';

    return 0;
}


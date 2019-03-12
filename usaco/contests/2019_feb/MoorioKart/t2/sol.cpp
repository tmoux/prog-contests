#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1505, M = 1e9+7;
int madd(int a, int b) {
    return (a+b) % M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}
int inverse(int x) {
    return modexp(x,M-2);
}
int ch2(int x) {
    return mult(mult(x,x-1),inverse(2));
}
int N, m, X, Y, K;

struct Edge
{
    int to, w;
};
vector<Edge> adj[maxn];
pair<int,int> dp[maxn][2505]; //keep (# of paths, total sum of paths) in each pair
bool seen[maxn];

pair<int,int> comb(pair<int,int> a, pair<int,int> b) {
    return {mult(a.first,b.first),
            madd(mult(a.first,b.second),mult(b.first,a.second))};
}

pair<int,int> operator+(const pair<int,int>& a, const pair<int,int>& b) {
    return {madd(a.first,b.first),madd(a.second,b.second)};
}

pair<int,int> operator+=(pair<int,int>& a, const pair<int,int>& b) {
    return a=a+b;
}

void ffill(int i, int p, vector<int>& comp) {
    seen[i] = true;
    comp.push_back(i);
    for (Edge e: adj[i]) {
        if (e.to != p) ffill(e.to,i,comp);
    }
}

void dfs_len(int i, int p, int orig, int d, map<int,pair<int,int>>& cnt) {
    if (i > orig) {
        cnt[min(Y,d)] += {1,d};
    }
    for (Edge e: adj[i]) {
        if (e.to != p) dfs_len(e.to,i,orig,d+e.w,cnt);
    }
}

 
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    freopen("mooriokart.in","r",stdin); freopen("mooriokart.out","w",stdout);
    cin >> N >> m >> X >> Y;
    K = N - m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dp[0][min(Y,K*X)] = {1,K*X};
    int pt = 1;
    for (int i = 1; i <= N; i++) {
        if (seen[i]) continue;
        vector<int> comp;
        ffill(i,i,comp);
        map<int,pair<int,int>> cnt;
        //maps weight to pair (# of paths, total sum of paths)
        for (int j: comp) dfs_len(j,j,j,0,cnt);
        for (auto p: cnt) {
            int wt = p.first;
            pair<int,int> pr = p.second;
            for (int y = 0; y <= Y; y++) {
                pair<int,int> add = comb(pr,dp[pt-1][y]);
                dp[pt][min(Y,y+wt)] += add;
            }
        }
        //cout << dp[pt][Y].second << '\n';
        pt++;
    }
    int ans = dp[K][Y].second;
    ans = mult(ans,modexp(2,K-1));
    for (int i = 2; i <= K-1; i++) ans = mult(ans,i);
    cout << ans << '\n';
}


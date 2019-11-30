#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n;

struct Segment
{
    int l, r, wt;
} segs[maxn];

vector<int> adj[maxn];
vector<Segment> v[maxn];
void dfs(int i, int p) {
    if (segs[i].l == 0) { 
        int min_l = maxn, max_r = 0;
        int sz = 0;
        for (int j: adj[i]) {
            if (j == p) continue;
            dfs(j,i);
            min_l = min(min_l,segs[j].l);
            max_r = max(max_r,segs[j].r);
            sz += segs[j].wt;
        }
        segs[i] = {min_l,max_r,sz};
        if (i != 1) segs[i].wt++;
    }
    v[segs[i].l].push_back(segs[i]);
    //printf("%d: l = %d, r = %d, wt = %d\n",i,segs[i].l,segs[i].r,segs[i].wt);
}

int dp[maxn];

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int a; cin >> a;
    for (int i = 2; i <= a; i++) {
        int pi; cin >> pi;
        adj[i].push_back(pi);
        adj[pi].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        int xi; cin >> xi;
        segs[xi] = {i,i,1};
    }
    dfs(1,1);
    int b; cin >> b;
    for (int i = 0; i < maxn; i++) {
        adj[i].clear();
        segs[i] = {0,0,0};
    }
    for (int i = 2; i <= b; i++) {
        int pi; cin >> pi;
        adj[i].push_back(pi);
        adj[pi].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        int xi; cin >> xi;
        segs[xi] = {i,i,1};
    }
    dfs(1,1);
    //calc dp
    for (int i = 1; i <= n; i++)  {
        for (auto s: v[i]) {
            dp[s.r] = max(dp[s.r],dp[s.l-1]+s.wt);
        }
    }
    cout << dp[n] << '\n';
}

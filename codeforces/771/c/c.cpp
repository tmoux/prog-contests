#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;
bool blocked[maxn];
int sub_size[maxn];

vector<int> adj[maxn];

int dfsSize(int i, int p) {
    sub_size[i] = 1;
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        sub_size[i] += dfsSize(j,i);
    }
    return sub_size[i];
}

int getCentroid(int i, int p, int compSize) {
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        if (sub_size[j] * 2 > compSize) return getCentroid(j,i,compSize);
    }
    return i;
}

ll ans = 0;

int cnt[6];
ll sum[6];

void dfs(int i, int p, int d, vector<int>& dist) {
    dist.push_back(d);
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        dfs(j,i,d+1,dist);
    }
}

void solve(int centroid) {
    for (int i = 0; i < 6; i++) {
        cnt[i] = sum[i] = 0;
    }
    cnt[0] = 1;
    for (int j: adj[centroid]) {
        if (blocked[j]) continue;
        vector<int> dist;
        dfs(j,centroid,1,dist);
        for (int d: dist) {
            for (int i = 0; i < k; i++) {
                int add = (d+i) % k == 0 ? 0 : k - ((d+i)%k);
                ans += (sum[i]+1LL*(d+add)*cnt[i])/k;
            }
        }
        //cout << j << ": " << ans << endl;
        for (int d: dist) {
            cnt[d%k]++;
            sum[d%k] += d;
        }
    }
}

void decomp(int i) {
    int compSize = dfsSize(i,i);
    int centroid = getCentroid(i,i,compSize);
    blocked[centroid] = true;
    solve(centroid);
    for (int j: adj[centroid]) {
        if (blocked[j]) continue;
        decomp(j);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    decomp(1);
    cout << ans << '\n';
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6+6;
int n, a[N];
vector<int> adj[N];

int dp[N][2]; //0 is longest path w/ end at i, 1 is longest overall
int anc[N];
void f(int i, int p) {
    if (a[i] == 1) {
        anc[i] = anc[p] + 1;
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        f(j,i);
    }
    if (a[i] == 1) {
        vector<int> v;
        //cout << i << ": ";
        for (int j: adj[i]) {
            if (j == p) continue;
            v.push_back(dp[j][0]);
            //cout << dp[j][0] << ' ';
        }
        //cout << '\n';
        sort(v.begin(),v.end(),greater<int>());
        dp[i][0] = dp[i][1] = 1;
        if (v.size() > 0) {
            dp[i][0] += v[0];
            dp[i][1] += v[0];
        }
        if (v.size() > 1) {
            dp[i][1] += v[1];
        }
    }
}

int chain[N];
void f2(int i, int p) {
    for (int j: adj[i]) {
        if (j == p) continue;
        f2(j,i);
    }
    if (a[i] == 2) {
        vector<int> v;
        for (int j: adj[i]) {
            if (j == p) continue;
            v.push_back(dp[j][0]);
        }
        v.push_back(anc[p]);
        sort(v.begin(),v.end(),greater<int>());
        if (v.size() >= 2 && v[0] == v[1]) {
            chain[i] = v[0]+v[1]+1;
        }
    }
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int mn = 2e9;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mn = min(mn,a[i]);
    }
    f(n,0);
    f2(n,0);
    int longest = 0;
    int c = 0;
    for (int i = 1; i <= n; i++) {
        longest = max(longest,dp[i][1]);
        c = max(c,chain[i]);
    }
    if (longest == 0) {
        printf("%d/%d\n",mn,1);
    }
    else {
        if (c == 0) {
            printf("%d/%d\n",1,longest);
            return 0;
        }
        assert(c != 0 && longest != 0);
        if ((double)(2)/c < (double)(1)/longest) {
            printf("%d/%d\n",2,c);
        }
        else {
            printf("%d/%d\n",1,longest);
        }
    }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<int,int> cnt;
vector<pair<int,int>> vec;
vector<int> divs;
void factor(int n) {
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                cnt[i]++;
                n /= i;
            }
            factor(n);
            return;
        }
    }
    if (n > 1) cnt[n]++;
}
void recurse(int i, int v) {
    if (i < vec.size()) {
        int mult = 1;
        for (int j = 0; j <= vec[i].second; j++) {
            if (j > 0) divs.push_back(v*mult);
            recurse(i+1,v*mult);

            mult *= vec[i].first;
        }
    }
}

vector<int> mp[1<<11];

const int maxm = 11;
int dp[maxm][maxm][1<<maxm];

int f(int i, int prev, int mask) {
    for (int j = 1; j <=     
}

void solve() {
    int n; cin >> n;
    cnt.clear();
    vec.clear();
    divs.clear();
    divs.reserve(100);
    factor(n);
    for (auto p: cnt) vec.push_back(p);
    recurse(0,1);

    //group by bitset of 0's
    int m = (1<<vec.size())-1;
    for (int i = 0; i <= m; i++) {
        mp[i].clear();
        mp[i].reserve(10);
    }
    for (auto u: divs) {
        int mask = 0;
        for (int i = 0; i < vec.size(); i++) {
            if (u % vec[i].first == 0) mask |= 1<<i;
        }
        mp[mask].push_back(u);
    }
    int best = n+5;
    vector<int> best_order;

    int sz = vec.size();
    for (int i = 0; i < sz; i++) {
        st = i;
        int ans n;
        for (int j = 0; j < sz; j++) ans = min(ans,dp[sz-1][j][m];
        if (ans < best) {
            vector<int> re = recon(1,i,1<<i);
            best = ans;
            best_order = re;
        }
    }

    for (auto i: best_order) {
        if (i != m) {
            for (auto j: mp[i]) {
                cout << j << ' ';
            }
        }
        else {
            int j = mp[m].back();
            mp[m].pop_back();
            cout << j << ' ';
        }
    }
    cout << '\n';
    cout << best << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

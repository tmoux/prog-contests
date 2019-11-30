#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
vector<pair<int,int>> v;

ll dp[maxn];
ll INF = 1e18;
int p[maxn], t[maxn];

int pt = 0;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(),v.end());
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        p[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 3; j <= 5 && i+j <= n; j++) {
            int diff = v[i+j-1].first-v[i].first;
            if (dp[i+j] > dp[i]+diff) {
                p[i+j] = i;
                dp[i+j] = dp[i] + diff;
            }
        }
    }
    int cur = n;
    int cnt = 0;
    while (cur != 0) {
        for (int i = cur-1; i >= p[cur]; i--) {
            t[v[i].second] = cnt;
        }
        cnt++;
        cur = p[cur];
    }
    cout << dp[n] << ' ' << cnt << '\n';
    for (int i = 0; i < n; i++) {
        cout << t[i]+1 << ' ';
    }
    cout << '\n';
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
string ss;

int dp[maxn], nxt[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    cin >> ss;
    set<pair<int,int>> s;
    s.insert({0,n});
    for (int i = n-1; i >= 0; i--) {
        if (ss[i] == '0' && !s.empty()) {
            auto p = *s.begin();
            dp[i] = p.first + 1;
            nxt[i] = p.second;
            s.insert({dp[i],i});
            /*
            cout << i << ": " << dp[i] << '\n';
            cout << "nxt = " << nxt[i] << '\n';
            */
        }
        if (i+m <= n && s.count({dp[i+m],i+m})) {
            s.erase({dp[i+m],i+m});
        }
    }
    if (nxt[0] != 0) {
        int cur = 0;
        while (true) {
            int next = nxt[cur];
            cout << next-cur << ' ';
            cur = next;
            if (cur == n) break;
        }
        cout << '\n';
    }
    else {
        cout << -1 << '\n';
    }
}


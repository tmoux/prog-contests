#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1050;
int n;
int s[maxn];

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    int ans = 2e9;
    for (int i = 1; i < n; i++) {
        int x = s[i] ^ s[0];
        set<int> mp;
        for (int j = 0; j < n; j++) {
            mp.insert(s[j]^x);
        }
        bool poss = true;
        for (int j = 0; j < n; j++) {
            if (!mp.count(s[j])) {
                poss = false;
                break;
            }
        }
        if (poss) ans = min(ans,x);
    }
    if (ans < 1e9) {
        cout << ans << '\n';
    }
    else {
        cout << -1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}

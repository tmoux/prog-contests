#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, r; cin >> n >> r;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    int mn = -1;
    bool poss = true;
    while (mn < n-1) {
        int p = -1;
        for (int i = min(n-1,r+mn); i >= 0 && i > mn-r+1; i--) {
            if (a[i] && i <= r+mn) {
                p = i;
                break;
            }
        }
        if (p == -1) {
            poss = false;
            break;
        }
        ans++;
        mn = p+r-1;
    }
    if (!poss) cout << -1 << '\n';
    else cout << ans << '\n';
}


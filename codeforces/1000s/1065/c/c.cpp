#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;
int h[maxn], x[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    int mn = 2e5+5;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        mn = min(mn,h[i]);
        mx = max(mx,h[i]);
    }
    if (mn == mx) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 0; i < n; i++) {
        h[i] -= mn;
        x[0]++;
        x[h[i]+1]--;
    }
    for (int i = 1; i <= 200000; i++) {
        x[i] += x[i-1];
        //if (i < 10) cout << i << ": " << x[i] << '\n';
    }
    int ans = 1;
    int curr = 0;
    for (int i = 200000; i >= 1; i--) {
        if (curr + x[i] <= k) {
            curr += x[i];
        }
        else {
            curr = x[i];
            ans++;
        }
    }
    cout << ans << '\n';
}


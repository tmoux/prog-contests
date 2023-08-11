#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n, a[maxn];

void solve() {
    cin >> n;
    int total = 0;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
        mx = max(mx,a[i]);
    }
    if (mx*2 > total) {
        cout << "T\n";
        return;
    }
    cout << (total%2==0?"HL":"T") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

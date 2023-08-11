#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n;
int a[maxn], b[maxn];
ll c[4*maxn];

ll f(int l, int r) {
    if (l == r) return 0;
    int m = (l+r)/2;
    ll minLeft = 1e18;
    ll cursum = 0;
    for (int i = m; i >= l; i--) {
        cursum += c[i];
        if (i % 2 == 1) minLeft = min(minLeft,cursum);
    }
    cursum = 0;
    ll ans = 1e18;
    for (int i = m+1; i <= r; i++) {
        cursum += c[i];
        if (i % 2 == 1) ans = min(ans,cursum+minLeft);
    }
    //cout << l << ' ' << r << ": " << ans << ' ' << minLeft << endl;
    ans = min(ans,f(l,m));
    ans = min(ans,f(m+1,r));
    return ans;
}

void solve() {
    cin >> n;
    ll sa = 0, sb = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sa += a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        sb += b[i];
    }
    if (sa > sb) {
        cout << "NO\n";
        return;
    }
    for (int i = 0; i < 2*n; i++) {
        c[2*i] = -a[i%n];
        c[2*i+1] = b[i%n];
    }
    ll mn = f(0,4*n-1);
    /*
    for (int i = 0; i < 4*n; i++) {
        cout << c[i] << ' ';
    }
    cout << '\n';
    cout << "mn = " << mn << endl;
    */
    cout << (mn>=0?"YES":"NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

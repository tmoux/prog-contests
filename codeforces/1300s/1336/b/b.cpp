#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

ll sqr(ll a) {
    return a*a;
}

ll calc(vector<int>& a, vector<int>& b, vector<int>& c) {
    int i = 0, j = 0;
    ll res = 4e18;
    for (int A: a) {
        //cout << A << endl;
        while (i+1 < b.size() && b[i+1] <= A) ++i;
        while (j < c.size() && c[j] < A) ++j;
        if (i < b.size() && j < c.size() && b[i] <= A && A <= c[j]) {
            res = min(res,sqr(b[i]-A)+sqr(c[j]-A)+sqr(b[i]-c[j]));
        }
    }
    return res;
}

void solve() {
    int nr, ng, nb; cin >> nr >> ng >> nb;
    vector<int> a(nr), b(ng), c(nb);
    for (int i = 0; i < nr; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < ng; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < nb; i++) {
        cin >> c[i];
    }
    sort(all(a));
    sort(all(b));
    sort(all(c));
    ll ans = 4e18;
    ans = min(ans,calc(a,b,c));
    ans = min(ans,calc(a,c,b));
    ans = min(ans,calc(b,a,c));
    ans = min(ans,calc(b,c,a));
    ans = min(ans,calc(c,a,b));
    ans = min(ans,calc(c,b,a));
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

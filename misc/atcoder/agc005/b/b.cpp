#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn], pos[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    ll ans = 0;
    set<int> s;
    s.insert(-1);
    s.insert(n);
    for (int i = 1; i <= n; i++) {
        int r = *s.upper_bound(pos[i]);
        int l = *prev(s.upper_bound(pos[i]));
        ans += 1LL*i*(r-pos[i])*(pos[i]-l);
        s.insert(pos[i]);
    }
    cout << ans << '\n';
}

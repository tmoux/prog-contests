#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, Q;
int v[maxn], m[maxn];
ll ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        cin >> m[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= N; i++) {
        ans[i] = m[i] + ans[v[i]];
    }
    for (int i = 1; i <= N; i++) {
        ans[i] = max(ans[i],ans[i-1]);
    }
    while (Q--) {
        ll p, c; cin >> p >> c;
        ll x = c-p;
        if (x <= 0 || x > ans[N]) {
            cout << -1 << '\n';
        }
        else {
            auto it = lower_bound(ans+1,ans+N+1,x);
            //cout << p << ' ' << c << ": " << *it << endl;
            cout << (it-ans) << endl;
        }
    }
}


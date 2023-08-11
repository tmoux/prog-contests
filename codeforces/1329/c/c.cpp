#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1<<22;
int h, g, n;
int a[maxn];
int depth[maxn];
int next_zero[maxn]; //depth of next zero if call f(i)

void upd(int i) {
    if (a[2*i] == 0 && a[2*i+1] == 0) {
        next_zero[i] = depth[i];
    }
    else if (a[2*i] > a[2*i+1]) {
        next_zero[i] = next_zero[2*i];
    }
    else {
        next_zero[i] = next_zero[2*i+1];
    }
}

void f(int i) {
    if (a[2*i] == 0 && a[2*i+1] == 0) {
        a[i] = 0;
    }
    else if (a[2*i] > a[2*i+1]) {
        a[i] = a[2*i];
        f(2*i);
    }
    else {
        a[i] = a[2*i+1];
        f(2*i+1);
    }
    upd(i);
}

ll ans = 0;
vector<int> v;

void recurse(int i) {
    //cout << i << endl;
    while (next_zero[i] > g) {
        v.push_back(i);
        ans -= a[i];
        f(i);
    }
    if (a[i*2] != 0) recurse(i*2);
    if (a[i*2+1] != 0) recurse(i*2+1);
}

void solve() {
    cin >> h >> g;
    n = (1<<h)-1;
    for (int i = 1; i <= 2*n+1; i++) {
        a[i] = 0;
        depth[i] = 0;
        next_zero[i] = 0;
    }
    ans = 0;
    v.clear();
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ans += a[i];
        depth[i] = i == 1 ? 1 : depth[i/2] + 1;
    }
    for (int i = n; i >= 1; i--) {
        upd(i);
    }
    recurse(1);

    cout << ans << '\n';
    for (auto i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

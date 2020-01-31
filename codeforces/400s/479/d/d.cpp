#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, l, a[maxn];
set<int> s;
int x, y;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> l >> x >> y;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    bool foundX = false, foundY = false;
    for (int i = 1; i <= n; i++) {
        s.insert(a[i]);
        if (s.count(a[i]-x)) foundX = true;
        if (s.count(a[i]-y)) foundY = true;
    }
    if (foundX && foundY) {
        cout << 0 << '\n';
        return 0;
    }
    if (foundX) {
        cout << 1 << '\n';
        cout << y << '\n';
        return 0;
    }
    if (foundY) {
        cout << 1 << '\n';
        cout << x << '\n';
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        int mk = a[i]+x;
        if (mk <= l && (s.count(mk-y) || s.count(mk+y))) {
            cout << 1 << '\n';
            cout << mk << '\n';
            return 0;
        }
        mk = a[i]-x;
        if (mk >= 1 && (s.count(mk-y) || s.count(mk+y))) {
            cout << 1 << '\n';
            cout << mk << '\n';
            return 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        int mk = a[i]+y;
        if (mk <= l && (s.count(mk-x) || s.count(mk+x))) {
            cout << 1 << '\n';
            cout << mk << '\n';
            return 0;
        }
        mk = a[i]-y;
        if (mk >= 1 && (s.count(mk-x) || s.count(mk+x))) {
            cout << 1 << '\n';
            cout << mk << '\n';
            return 0;
        }
    }
    cout << 2 << '\n';
    cout << x << ' ' << y << '\n';
}


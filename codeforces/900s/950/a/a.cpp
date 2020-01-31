#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int l, r, a; cin >> l >> r >> a;
    int ans = min(l,r);
    l -= ans;
    r -= ans;
    int add = min(l,a);
    ans += add;
    a -= add;
    add = min(r,a);
    ans += add;
    a -= add;
    ans += a/2;
    cout << 2*ans << '\n';
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b, c; cin >> a >> b >> c;
        vector<int> v;
        v = {a,b,c};
        sort(v.begin(),v.end());
        a = v[0];
        b = v[1];
        c = v[2];
        int diff = c-b;
        int ans = min(a,diff);
        a -= ans;
        c -= ans;
        //cout << a << ' ' << b << ' ' << c << '\n';
        if (a == 0) {
            ans += min(b,c);
            cout << ans << '\n';
        }
        else {
            ans += a/2;
            b -= a/2;
            ans += a/2;
            c -= a/2;
            ans += min(b,c);
            cout << ans << '\n';
        }
    }
}


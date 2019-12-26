#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b, c, r; cin >> a >> b >> c >> r;
        if (a > b) swap(a,b);
        int len = abs(b-a);
        int ll = c-r;
        int rr = c+r;
        int mxL = max(ll,a);
        int mnR = min(b,rr);
        int cover = max(0,mnR-mxL);
        cout << len-cover << endl;
    }
}


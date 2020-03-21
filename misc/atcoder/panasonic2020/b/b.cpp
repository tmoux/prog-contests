#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int h, w; cin >> h >> w;
    if (h == 1 || w == 1) {
        cout << 1 << endl;
        return 0;
    }
    int n1 = (w+1)/2;
    int n2 = w/2;
    int m1 = (h+1)/2;
    int m2 = h/2;
    ll ans = 1LL*n1*m1+1LL*n2*m2;
    cout << ans << endl;
}

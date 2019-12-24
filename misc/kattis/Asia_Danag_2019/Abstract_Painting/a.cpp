#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 1e9+7;
int R, C;

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int modexp(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (b&1) r = mult(r,a);
        a = mult(a,a);
        b >>= 1;
    }
    return r;
}

int main() {
    int t; cin >> t;
    while (t--) {
        cin >> R >> C;
        int ans = 18;
        ans = mult(ans,modexp(6,R-1));
        ans = mult(ans,modexp(6,C-1));
        ans = mult(ans,modexp(2,(R-1)*(C-1)));
        cout << ans << '\n';
    }
}

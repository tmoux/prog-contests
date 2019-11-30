#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll A, B, X;

int d(ll x) {
    int res = 0;
    while (x > 0) {
        res++;
        x /= 10;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> A >> B >> X;
    ll l = 0, r = 1e9+1;
    while (l + 1 < r) {
        ll mid = (l+r)/2;
        ll n = A*mid+B*d(mid);
        if (n <= X) {
            l = mid;
        }
        else r = mid;
    }
    cout << l << '\n';
}


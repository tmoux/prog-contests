#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll f(ll n) {
    ll res = 0;
    while (n % 2 == 0) {
        n /= 2;
        res += n;
    }
    res += n*(n-1)/2;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    /*
    for (int i = 1; i <= 20; i++) {
        cout << i << ": " << f(i) << '\n';
    }
    */
}


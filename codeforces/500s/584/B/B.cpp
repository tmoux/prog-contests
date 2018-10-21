#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int MOD = 1000000007;
ll modexp(ll x, int n) {
    if (n == 0) return 1;
    if (n == 1) return x % MOD;
    if (n % 2 == 0) return modexp(x*x % MOD, n/2);
    if (n % 2 == 1) return (x * modexp(x*x % MOD, n/2)) % MOD;
}

ll mod(ll a) {
    while (a < 0) {
        a += MOD;
    }
    return a;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n; cin >> n;
    ll ans = mod(modexp(27,n) - modexp(7,n));
    cout << ans << '\n';

    return 0;
}
	


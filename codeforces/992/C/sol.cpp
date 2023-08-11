#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int MOD = 1000000007;
ll x, k;

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x % MOD;
    if (n % 2 == 0) return modexp(x*x % MOD, n/2) % MOD;
    if (n % 2 == 1) return (x * modexp(x*x % MOD, n/2)) % MOD;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> x >> k;
    if (x == 0) {
        cout << 0 << '\n';
        return 0;
    }
    if (k == 0) {
        cout << ((2*x) % MOD) << '\n';
        return 0;
    }
    ll a = (2*x-1) % MOD;
    cout << (2*a*modexp(2,k-1) + 1) % MOD << '\n';

    return 0;
}
	


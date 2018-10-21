#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
const int M = 1e9+7;

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n; cin >> n;
    ll num = modexp(1,n);
    ll den = modexp(2,n);
    ll ans = (num + den) % M;
    cout << ans << '\n';


    return 0;
}
	


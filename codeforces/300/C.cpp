#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5;
const int M = 1e9+7;
int a, b, n;

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

ll fac[maxn];

ll choose(ll n, ll r) {
	return ((fac[n] * modexp(fac[r],M-2)) % M * modexp(fac[n-r],M-2))%M;
}

bool isValid(int ss) {
	while (ss) {
		if (ss % 10 != a && ss % 10 != b) {
			return false;
		}
		ss /= 10;
	}
	return true;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
	#endif
	cin >> a >> b >> n;
	//precomp
	fac[0] = 1;
	for (int i = 1; i <= n; i++) {
		fac[i] = (fac[i-1]*i)%M;
	}	

	//calculate
	ll ans = 0LL;
	for (int i = 0; i <= n; i++) {
		//i is # of b's
		int curr = (n-i)*a + i*b;
		if (isValid(curr)) {
			ans = (ans + choose(n,i))%M;
		}
	}

	cout << ans << '\n';

	
	
	return 0;
}
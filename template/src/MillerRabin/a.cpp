#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

ll multiply(ll a, ll b, ll M) {
	ll res = 0;
	a %= M;
	while (b) {
		if (b&1) res = (res + a) % M;
		a = (2*a) % M;
		b >>= 1;
	}
	return res;
}

ll modexp(ll x, ll n, ll M) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp(multiply(x,x,M),n/2,M);
    return multiply(x,modexp(multiply(x,x,M),n/2,M),M);
}

bool miller_rabin(ll b, ll p) {
	//returns true if p might be prime, false if definitely NOT prime
	ll s = p - 1;
	while (s % 2 == 0) s /= 2;
	ll r = modexp(b,s,p);
	ll r1 = modexp(b,p-1,p);
	if (r == 1 || r == p-1) return true;
	while (s < p - 1) {
		s *= 2;
		r = multiply(r,r,p);
		if (r == p-1) return true;
		if (r == 1) return false;
	}
	return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll primes[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    int t; cin >> t;
    while (t--) {
    	ll p; cin >> p;
    	bool isPrime = true;
    	for (int k = 0; k < 500; k++) {
    		ll b = 2+(rand()%(p-4));
    		isPrime &= miller_rabin(b,p);
    		if (!isPrime) break;
    	}
    	cout << (isPrime ? "YES" : "NO") << '\n';
    }

    return 0;
}


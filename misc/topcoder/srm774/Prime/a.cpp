#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

bool brute(ll p) {
    if (p == 1) return false;
    for (ll i = 2; i*i <= p; i++) {
        if (p % i == 0) return false;
    }
    return true;
}

bool is_prime(ll p) {
    if (p < 100) {
        return brute(p);
    }
    ll primes[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    bool isPrime = true;
    for (ll b: primes) {
        if (b >= p-3) continue;
        isPrime &= miller_rabin(b,p);
        if (!isPrime) break;
    }
    return isPrime;
}

ll string_to_int(string s) {
    ll res = 0;
    ll mult = 1;
    for (int i = s.size()-1; i >= 0; i--) {
        res += (s[i]-'0')*mult;
        mult *= 10;
    }
    return res;
}

string int_to_string(ll x) {
    string res;
    while (x > 0) {
        res += (x%10)+'0';
        x /= 10;
    }
    reverse(res.begin(),res.end());
    return res;
}

class PrimeWithSubstring
{
public:
    ll findPrime(int N) {
        if (N == 0) return 4021;
        string s = int_to_string(N);
        for (int add = 1; ; add += 2) {
            string ss = s+int_to_string(add);
            ll tr = string_to_int(ss);
            //cout << tr << ": " << is_prime(tr) << endl;
            if (is_prime(tr)) {
                return tr;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    PrimeWithSubstring t;
    int n; cin >> n;
    ll ans = t.findPrime(n);
    cout << ans << endl;
    assert(brute(ans));
}


ll modexp(ll x, ll n, int M) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2,M);
    return (x*modexp((x*x)%M,n/2,M))%M;
}

//assume M is prime
ll modInverse(ll x, int M) {
	return modexp(x,M-2);
}


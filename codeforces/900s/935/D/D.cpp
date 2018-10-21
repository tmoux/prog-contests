#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

typedef long long ll;
const int MOD = 1000000007;
const int maxn = 100002;
int N, M;
int s1[maxn], s2[maxn]; 

struct Fraction
{
	ll numer;
	ll denom;
	Fraction() {
		
	}
	Fraction(ll nu, ll de) {
		numer = nu;
		denom = de;
	}
	
	Fraction operator*(const Fraction& right) {
		return {(numer*right.numer) % MOD, (denom*right.denom) % MOD};
		//reduce();
	}
	Fraction operator+(const Fraction& right) {
		return {(numer*right.denom + denom*right.numer) % MOD, (denom*right.denom) % MOD};
		//reduce();
	}
	
	void reduce() {
		ll gcd = __gcd(numer,denom);
		numer /= gcd;
		denom /= gcd;
	}
	void print() {
		cout << numer << ' ' << denom << '\n';
	}
};

ll exp_square(ll x, ll n) {
	if (n == 0) return 1;
	else if (n ==1) return x;
	if (n % 2 == 0) return exp_square((x*x) % MOD, n/2) % MOD;
	else return (x*(exp_square((x*x) % MOD, (n-1)/2))) % MOD;
}

ll findR(ll P, ll Q) 
{
	return (P*exp_square(Q,MOD-2)) % MOD;
}

Fraction calc(int i) {
	ll numer;
	if (i == N) return {0,1};
	if (s1[i] != 0 && s2[i] != 0) {
		if (s1[i] > s2[i]) {
			return {1,1};
		}
		if (s1[i] < s2[i]) {
			return {0,1};
		}
		return calc(i+1);
	}
	int s1i = s1[i];
	int s2i = s2[i];
	Fraction fir;
	if (s1[i] == 0 && s2[i] == 0) {
		fir = {M-1,2*M};
	}
	else if (s1[i] == 0) {
		fir = {M-s2[i],M};
	}
	else if (s2[i] == 0) {
		fir = {s1[i]-1,M};
	}
	Fraction sec = calc(i+1);
	return fir + sec * Fraction(1,M);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	
	cin >> N >> M;
	for (int j = 0; j < N; j++) {
		cin >> s1[j];
	}
	for (int j = 0; j < N; j++) {
		cin >> s2[j];
	}
	
	Fraction pq = calc(0);
	pq.reduce();
	ll ans = findR(pq.numer,pq.denom);
	//pq.print();
	cout << ans << '\n';
	
	return 0;
}


#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
int n, a[maxn], h[maxn];
int ntoHash[75];
vector<int> primes;
map<int,int> cnt;
const int M = 1e9+7;

void madd(int& a, int b) {
	a += b;
	if (a > M) a -= M;
}
int mult(int a, int b) {
	return (1LL*a*b) % M;
}

bool isPrime(int x) {
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) return false;
	}
	return true;
}

int hsh(int x) {
	int res = 0;
	for (int i = 0; i < primes.size(); i++) {
		int t = 0;
		while (x % primes[i] == 0) {
			x /= primes[i];
			t ^= 1;
		}
		res |= (t<<i);
	}
	return res;
}

int dp[2][1<<20];
int pow2[maxn];

int main() {
	cin >> n;
	for (int i = 2; i <= 70; i++) {
		if (isPrime(i)) {
			primes.push_back(i);
		}
		ntoHash[i] = hsh(i);
	}
	pow2[0] = 1;
	for (int i = 1; i <= n; i++) {
		pow2[i] = (2LL*pow2[i-1]) % M;
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		cnt[ntoHash[a[i]]]++;
	}
	dp[0][0] = 1;
	int t = 0;
	for (auto p: cnt) {
		//cout << p.first << ' ' << p.second << '\n';
		int w0 = pow2[p.second-1];
		//cout << (p.second-1) << ": " << w0 << '\n';
		for (int i = 0; i < (1<<19); i++) {
			dp[t^1][i] = (mult(dp[t][i],w0)+mult(dp[t][i^p.first],w0)) % M;
		}
		/*
		for (int i = 0; i < 5; i++) {
			cout << dp[t^1][i] << ' ';
		}
		cout << '\n';
		*/
		t ^= 1;
	}

	int ans = (dp[t][0]-1+M) % M;
	cout << ans << '\n';
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005, M = 1e9+7;

ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

int dp[maxn]; //# ways to make line of len i
struct Word
{
	int rclass, len;
} words[maxn];
int N, m, K;
void madd(int& a, int b) {
	a = (a+b) % M;
}

int waysForClass[maxn];

int main()
{
	freopen("poetry.in","r",stdin); freopen("poetry.out","w",stdout);
	cin >> N >> m >> K;
	for (int i = 0; i < N; i++) {
		cin >> words[i].len >> words[i].rclass;
	}
	//fill in dp
	dp[0] = 1;
	for (int i = 1; i <= K; i++) {
		for (int j = 0; j < N; j++) {
			if (i - words[j].len >= 0) {
				madd(dp[i],dp[i-words[j].len]);
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		//update waysForClass
		for (int j = 0; j < N; j++) {
			if (words[j].rclass == i) {
				madd(waysForClass[i],dp[K-words[j].len]);
			}
		}
	}
	map<char,int> cnt;
	for (int i = 0; i < m; i++) {
		char c; cin >> c;
		cnt[c]++;
	}
	ll res = 1;
	for (auto p: cnt) {
		int n = p.second;
		int add = 0;
		for (int i = 1; i <= N; i++) {
			madd(add,modexp(waysForClass[i],n));
		}
		res = (res * add) % M;
	}
	cout << res << '\n';
}
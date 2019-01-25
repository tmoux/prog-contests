#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1000000033, base = 6969;
inline int ctoi(char c) { return c-'a'+1; }

ll modexp(ll x, ll n) {
    ll res = 1;
	while (n) {
		if (n&1) res = (res*x) % M;
		x = (x*x) % M;
		n >>= 1;
	}
	return res;
}

ll pfx[maxn], inv[maxn];
char ans[maxn];

ll hsh(const string& s) {
	ll res = 0;
	ll mult = 1;
	for (int i = 0; i < (int)s.size(); i++) {
		res = (res + mult*ctoi(s[i])) % M;
		mult = (mult * base) % M;
	}
	return res;
}

map<int,set<ll>> hashes;

ll getSuffix(int idx, int len) {
	assert(idx >= len);
	return ((pfx[idx]-pfx[idx-len]+M)%M * inv[idx-len]) % M;
}

int main()
{
	freopen("censor.in","r",stdin); 
	freopen("censor.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string S; cin >> S;
    int sz = S.size();
    int N; cin >> N;
    int big = 1;
	for (int i = 0; i < N; i++) {
		string t; cin >> t;
		hashes[t.size()].insert(hsh(t));
	}
	//set up inverses
	inv[0] = 1;
	inv[1] = modexp(base,M-2);
	for (int i = 2; i <= 100000; i++) {
		inv[i] = (inv[i-1] * inv[1]) % M;
	}
	int idx = 1;
	for (int i = 0; i < sz; i++) {
		bool found = false;
		//add next char
		pfx[idx] = (pfx[idx-1] + modexp(base,idx-1) * ctoi(S[i])) % M;
		ans[idx] = S[i];
		for (auto& p: hashes) {
			int len = p.first;
			if (len > idx) continue;
			ll suff = getSuffix(idx,len);
			if (p.second.count(suff)) {
				found = true;
				idx -= len;
				break;
			}
		}
		++idx;
	}
	//output answer
	for (int i = 1; i < idx; i++) {
		cout << ans[i];
	}
	cout << '\n';
    return 0;
}













/*
	together.cpp
	Solution to "Berland Bands Together"
	SIUCF CompProg Camp 2018, Contest 5

	solution by Charles B.

	18 July 2018
*/
#include <bits/stdc++.h>

typedef long long ll;

const static ll INF = 0x3f3f3f3f3f3f3f3f;

static inline void setio(void);

const ll MAX_N = 501;

ll c[MAX_N], ls[MAX_N];
ll memo[MAX_N][MAX_N];

int main(void) {
	setio();

	memset(memo, 0x3f, sizeof(memo));

	ll n; std::cin >> n;

	for (ll i = 0; i < n; ++i) {
		std::cin >> ls[i];
		memo[i][i] = 0;
	}
	for (ll i = 0; i < n; ++i)
		std::cin >> c[i];

	for (ll l = 0; l + 1 < n; ++l) {
		const ll r = l + 1;
		memo[l][r] = (ls[l] + ls[r]) * std::min(c[l], c[r]);
	}

	for (ll amt = 2; amt < n; ++amt) {
		for (ll l = 0; l < n && l + amt < n; ++l) {
			const ll r = l + amt;
			ll ls_s = 0; for (ll i = l; i <= r; ++i) ls_s += ls[i];
			for (ll i = l; i < r; ++i) {
				memo[l][r] = std::min(memo[l][r], ls_s * std::min(c[i], c[i+1]) + memo[l][i] + memo[i+1][r]);
			}
		}
	}

	const ll iterative_ans = memo[0][n-1];

	// std::function<ll(const ll&, const ll&)>
	// go = [&](const ll& l, const ll& r) {
	// 	if (l >= r)
	// 		return 0LL;
	// 	if (memo[l][r] != -1)
	// 		return memo[l][r];
	// 	ll ret = INF, ls_s = 0; for (ll i = l; i <= r; ++i) ls_s += ls[i];
	// 	for (ll i = l; i < r; ++i)
	// 		ret = std::min(ret, ls_s * std::min(c[i], c[i+1]) + go(l, i) + go(i+1, r));
	// 	return memo[l][r] = ret;
	// };

	// memset(memo, 0xff, sizeof(memo));

	// const ll recursive_ans = go(0, n-1);

	// assert(iterative_ans == recursive_ans);

	std::cout << iterative_ans << "\n";

	std::cerr << static_cast<double>(clock())/CLOCKS_PER_SEC << "\n";

	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}

/*
	memes.cpp
	Solution to "Dank Memes"
	SIUCF CompProg Camp 2018, Contest 5

	problem and solution by Charles B.

	17 July 2018
*/
#include <bits/stdc++.h>

typedef long long ll;

static inline void setio(void);

const ll MAX_N = 4001;

struct dank_meme {
	ll r, d;
} memes[MAX_N];

ll n, R;
ll memo[MAX_N][MAX_N];

int main(void) {
	setio();

	std::memset(memo, 0xff, sizeof(memo));

	std::cin >> n >> R;
	for (ll i = 0; i < n; ++i)
		std::cin >> memes[i].r >> memes[i].d;

	std::function<ll(const ll&, const ll&)>
	go = [&](const ll& cur, const ll& r_left) {
		if (cur >= n || r_left == 0) return 0LL;
		if (memo[cur][r_left] != -1) return memo[cur][r_left];

		ll ret = go(cur+1, r_left);
		if (r_left >= memes[cur].r)
			ret = std::max(ret, memes[cur].d + go(cur+1, r_left - memes[cur].r));

		return memo[cur][r_left] = ret;
	};

	std::cout << go(0, R) << "\n";

	std::cerr << static_cast<double>(clock())/CLOCKS_PER_SEC << "\n";

	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}

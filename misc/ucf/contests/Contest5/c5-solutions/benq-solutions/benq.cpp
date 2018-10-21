/*
	benq.cpp
	Solution to "Ben Queue"
	SIUCF CompProg Camp 2018, Contest 5

	solution by Charles B.

	18 July 2018
*/
#include <bits/stdc++.h>

typedef long long ll;
typedef std::pair<ll,ll> pairll;

static inline void setio(void);

const ll MAX_N = 100001;
ll a[MAX_N];

int main(void) {
	setio();

	ll n; std::cin >> n;

	assert(n >= 1 && n <= 1000);
	for (ll i = 0; i < n; ++i) {
		std::cin >> a[i];
		assert(a[i] >= 1 && a[i] <= 10000000);
		a[i] = (i == 0 ? a[i] : std::min(a[i], a[i-1]));
	}

	ll ans = 0;
	for (ll i = 0, v; i < n; ++i) {
		std::cin >> v;
		assert(v >= 1 && v <= 10000000);
		ans += v * a[i];
	}

	std::cout << ans << "\n";

	std::cerr << static_cast<double>(clock())/CLOCKS_PER_SEC << "\n";

	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}

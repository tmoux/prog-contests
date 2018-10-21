/*
	subarray.cpp
	Solution to "FJ and Subarray"
	SIUCF CompProg Camp 2018, Contest 5

	problem and solution by Charles B.

	17 July 2018
*/
#include <bits/stdc++.h>

typedef long long ll;

const static ll INF = 0x3f3f3f3f3f3f3f3f;

static inline void setio(void);

#define ab std::abs

const ll MAX_N = 1001;

ll a[MAX_N], sum[MAX_N];

int main(void) {
	setio();

	memset(sum, 0, sizeof(sum));

	ll n, k; std::cin >> n >> k;
	for (ll i = 0; i < n; ++i)
		std::cin >> a[i];

	sum[0] = std::accumulate(a, a + k, 0);
	for (ll i = 1; i + k <= n; ++i) {
		sum[i] = sum[i-1] - a[i-1] + a[i+k-1];
	}

	ll hi = 0, hj = k;
	for (ll i = 0; i + 2 * k <= n; ++i) {
		const ll j = i + k;
		// for (ll j = i + k; j + k <= n; ++j) {
			const ll md = ab(sum[i] - sum[j]), hd = ab(sum[hi] - sum[hj]);
			const ll ms = sum[i] + sum[j], hs = sum[hi] + sum[hj];
			if (md < hd || (md == hd && ms > hs)) {
				hi = i; hj = j;
			}
		// }
	}

	std::cout << sum[hi] + sum[hj] << "\n";

	std::cerr << static_cast<double>(clock())/CLOCKS_PER_SEC << "\n";

	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}

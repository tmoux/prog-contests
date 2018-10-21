/*
	calories.cpp
	Solution to "Cookie Calories"
	SIUCF CompProg Camp 2018, Contest 5

	problem and solution by Charles B.

	18 July 2018
*/
#include <bits/stdc++.h>

typedef long long ll;

static inline void setio(void);

const ll MAX_N = 11;

ll m[MAX_N], M[MAX_N];

int main(void) {
	setio();

	memset(m, 0x3f, sizeof(m));
	memset(M, 0x00, sizeof(M));

	ll n; std::cin >> n;
	for (ll i = 0, k, v; i < n; ++i) {
		for (std::cin >> k; k--; ) {
			std::cin >> v;
			m[i] = std::min(m[i], v);
			M[i] = std::max(M[i], v);
		}
	}

	std::cout << std::accumulate(m, m + n, 0) << " " << std::accumulate(M, M + n, 0) << "\n";

	std::cerr << static_cast<double>(clock())/CLOCKS_PER_SEC << "\n";

	return 0;
}

static inline void setio(void) {
	std::ios::sync_with_stdio(false);std::cin.tie(nullptr);
	std::cout.precision(10); std::cout << std::fixed;
}

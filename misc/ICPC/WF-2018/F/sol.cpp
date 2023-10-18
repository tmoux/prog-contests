#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef long double ld; // change to double if appropriate
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define F0Rd(i, a) for (int i = (a) - 1; i >= 0; i--)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

const char nl = '\n';

void solve() {
	int N; cin >> N;
	vector<string> words(N);
	vector<int> len(N);
	int mxlen = 0;
	F0R(i, N) {
		cin >> words[i];
		len[i] = sz(words[i]);
		mxlen = max(mxlen, len[i]);
	}
	vector<vector<int>> space(2600);
	vector<vector<int>> dp(2600, vector<int>(2600));

	pair<int, int> best = {-1, -1};
	for (int W = mxlen; W <= 2600 * 81; W++) {
		int row = 0;
		int col = 0;
		F0R(i, N) {
			if (col + (col != 0) + len[i] > W) {
				row++;
				col = 0;
			}
			assert(col + (col != 0) + len[i] <= W);
			if (col > 0) {
				space[row].push_back(col);
				col++;
			}
			col += len[i];
		}
		// if (W == 15) {
		// 	FOR(r, 0, row+1) {
		// 		for (auto i: space[r]) {
		// 			cout << i << ' ';
		// 		}
		// 		cout << endl;
		// 	}
		// }

		int ans = 0;
		for (int r = 0; r <= row; r++) {
			if (r == 0) {
				F0R(j, sz(space[0])) dp[0][j] = 1;
			}
			else {
				int pt = 0;
				F0R(j, sz(space[r])) {
					pt = max(0, pt - 3);
					dp[r][j] = 1;
					while (pt < sz(space[r-1]) && space[r-1][pt] < space[r][j]-1) pt++;
					while (pt < sz(space[r-1]) && abs(space[r-1][pt] - space[r][j]) <= 1) {
						dp[r][j] = max(dp[r][j], dp[r-1][pt] + 1);
						pt++;
					}
				}
			}

			F0R(j, sz(space[r])) {
				ans = max(ans, dp[r][j]);
			}
		}

		if (ans > best.first) {
			best = {ans, W};
		}
		for (int i = 0; i <= row; i++) space[i].clear();
	}
	cout << best.second << ' ' << best.first << '\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	solve();
	return 0;
}

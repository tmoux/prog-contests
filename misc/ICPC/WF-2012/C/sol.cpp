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

const int maxn = 25;
int D[maxn][maxn];

int dpS[20][1 << 20], dpT[20][1 << 20];

void computeDist(int s, const vector<int>& v, int dp[20][1<<20]) {
	F0R(i, sz(v)) F0R(mask, 1 << sz(v)) dp[i][mask] = 1e9;
	F0R(i, sz(v)) dp[i][1 << i] = D[s][v[i]];
	FOR(m, 1, 1 << sz(v)) {
		if (__builtin_popcount(m) == 1) continue;
		F0R(i, sz(v)) {
			if (m & (1 << i)) {
				F0R(j, sz(v)) {
					if (i != j && (m & (1 << j))) {
						dp[i][m] = min(dp[i][m], dp[j][m^(1<<i)] + D[v[j]][v[i]]);
					}
				}
			}
		}
	}
};

int solve(int N, int M) {
	F0R(i, N) F0R(j, N) D[i][j] = 1e9;
	F0R(i, N) D[i][i] = 0;
	F0R(_, M) {
		int a, b, w; cin >> a >> b >> w;
		D[a][b] = min(D[a][b], w);
		D[b][a] = min(D[b][a], w);
	}
	F0R(k, N) {
		F0R(i, N) {
			F0R(j, N) {
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
			}
		}
	}
	if (N == 3) {
		return D[0][1] + D[1][2] + D[2][1] + D[1][0];
	}
	else {
		int ans = 2e9;
		int H = N - 2;
		int H_ALL = (1 << H) - 1;
		vector<int> v;
		for (int i = 1; i < N; i++) v.push_back(i);
		computeDist(0, v, dpS);
		computeDist(N-1, v, dpT);
		F0R(mask, 1 << H) {
			if (__builtin_popcount(mask) == H/2) {
				vector<int> S, T;
				F0R(i, H) (mask & (1 << i) ? S : T).push_back(i+1);
				int maskComp = H_ALL ^ mask;
				vector<int> sS(sz(S)), sT(sz(T));
				F0R(i, sz(S)) sS[i] = dpS[S[i]-1][mask];
				F0R(i, sz(T)) sT[i] = dpS[T[i]-1][maskComp];
				vector<int> tS(sz(S)), tT(sz(T));
				F0R(i, sz(S)) tS[i] = dpT[S[i]-1][mask];
				F0R(i, sz(T)) tT[i] = dpT[T[i]-1][maskComp];

				int t1 = 1e9;
				int t2 = 1e9;
				F0R(i, sz(S)) {
					F0R(j, sz(T)) {
						t1 = min(t1, sS[i] + D[S[i]][T[j]] + tT[j]);
						t2 = min(t2, tS[i] + D[S[i]][T[j]] + sT[j]);
					}
				}
				ans = min(ans, t1 + t2);
				// cout << t1 << ' ' << t2 << endl;
				// cout << "mask = " << mask << " " << t1+t2 << endl;
			}
		}
		return ans;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int N, M;
	int t = 1;
	while (cin >> N >> M) {
		cout << "Case " << t++ << ": " << solve(N, M) << endl;
	}
	return 0;
}

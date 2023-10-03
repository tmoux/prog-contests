#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const ll MOD = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
typedef vector<int> vi;

ll modExp(ll a, ll b) {
  ll res = 1;
  for (; b; a = (a * a) % MOD, b >>= 1)
    if (b & 1) res = (res * a) % MOD;
  return res;
}
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, modExp(root, MOD >> s)};
		FOR(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % MOD;
	}
	vi rev(n);
	FOR(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	FOR(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) F0R(j,k) {
			ll z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? MOD: 0);
			ai += (ai + z >= MOD ? z - MOD : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	int inv = modExp(n, MOD - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	F0R(i,n) out[-i & (n - 1)] = (ll)L[i] * R[i] % MOD * inv % MOD;
	ntt(out);
	return {out.begin(), out.begin() + s};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, K; cin >> N >> K;
  vl p(10);
  REP(K) {
    int d; cin >> d;
    p[d] = 1;
  }
  vl poly = {1};
  int n = N/2;
  while (n) {
    if (n&1) poly = conv(poly, p);
    p = conv(p, p);
    n >>= 1;
  }

  ll total = 0;
  for (auto x: poly) {
    total = (total + (x * x) % MOD) % MOD;
  }
  cout << total << '\n';
}

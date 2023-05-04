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

const int D = 19;
int dp[D+1][2][2][2][10][10];
vector<int> DL, DR;

int f(int i, int il, int ir, int s, int L, int R) {
  if (i < 0) {
    assert(L <= R);
    return R - L;
  }
  int& res = dp[i][il][ir][s][L][R];
  if (res != -1) return res;
  int mn = il ? 0 : DL[i];
  int mx = ir ? 9 : DR[i];

  res = 9;
  for (int d = mn; d <= mx; d++) {
    int ns = s || (d > 0);
    int nL = ns ? min(L, d) : L;
    int nR = ns ? max(R, d) : R;
    ckmin(res, f(i-1, il || d > DL[i], ir || d < DR[i], ns, nL, nR));
  }
  return res;
}

vector<int> V;
void recon(int i, int il, int ir, int s, int L, int R, int ans) {
  if (i < 0) return;
  int mn = il ? 0 : DL[i];
  int mx = ir ? 9 : DR[i];
  for (int d = mn; d <= mx; d++) {
    int ns = s || (d > 0);
    int nL = ns ? min(L, d) : L;
    int nR = ns ? max(R, d) : R;
    if (ans == f(i-1, il || d > DL[i], ir || d < DR[i], ns, nL, nR)) {
      V.push_back(d);
      recon(i-1, il || d > DL[i], ir || d < DR[i], ns, nL, nR, ans);
      break;
    }
  }
}

void solve() {
  ll L, R; cin >> L >> R;
  auto digits = [&](ll x) {
    vector<int> v;
    REP(D) {
      v.push_back(x % 10);
      x /= 10;
    }
    return v;
  };
  DL = digits(L);
  DR = digits(R);

  memset(dp, -1, sizeof dp);
  int ans = f(D-1, 0, 0, 0, 9, 0);
  V.clear();
  recon(D-1, 0, 0, 0, 9, 0, ans);
  for (int i = 0, start = 0; i < sz(V); i++) {
    if (V[i]) start = 1;
    if (start) cout << V[i];
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

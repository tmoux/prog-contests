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

const int M = 1e9 + 7;
void madd(int &a, int b) {
  a = (a + b) % M;
}

int solve() {
  ll b, q, y;
  cin >> b >> q >> y;
  ll c, r, z;
  cin >> c >> r >> z;
  ll L1 = b;
  ll R1 = b + (y - 1) * q;
  ll L2 = c;
  ll R2 = c + (z - 1) * r;

  auto in_bounds = [&](ll x) -> bool {
    return L1 <= x && x <= R1 && (x - L1) % q == 0;
  };
  ll L = L2 - r;
  ll R = R2 + r;

  auto lcm = [](ll a, ll b) { return a * b / __gcd(a, b); };

  if (!(lcm(q, r) == r && in_bounds(L2) && in_bounds(R2))) { return 0; }

  auto calc = [&](ll d) -> int {
    if (lcm(d, q) == r) {
      // cout << "checking " << d << '\n';
      // cout << L << ' ' << R << endl;
      if (in_bounds(L) && in_bounds(R)) {
        ll left = (L2 - L) / d;
        ll right = (R - R2) / d;
        return (left * right) % M;
      } else {
        return -1;
      }
    } else
      return 0;
  };

  int ans = 0;
  for (ll d = 1; d * d <= r; d++) {
    if (r % d == 0) {
      int cnt = calc(d);
      if (cnt == -1)
        return -1;
      else
        madd(ans, cnt);

      if (r / d != d) {
        cnt = calc(r / d);
        if (cnt == -1)
          return -1;
        else
          madd(ans, cnt);
      }
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  while (T--) { cout << solve() << '\n'; }
}


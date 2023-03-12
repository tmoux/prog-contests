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


using ld = long double;
const ll INF = 2e18;
ll mult(ll a, ll b) {
  ld d = (ld)a * b;
  if (d >= INF) return INF;
  else return a * b;
}
ll power(ll a, int b) {
  ll r = 1;
  REP(b) {
    r = mult(r, a);
  }
  return r;
}
ll add(ll a, ll b) {
  if (a + b >= INF) return INF;
  else return a + b;
}

bool check(ll N, ll b) {
  while (N > 0) {
    ll mod = N % b;
    if (mod == 0 || mod == 1) {
      N = (N - mod) / b;
    }
    else {
      return false;
    }
  }
  return true;
}

void solve(ll N) {
  int K = 4;
  int ans = 0;
  F0R(mask, 1 << K) {
    vector<int> c(K);
    F0R(i, K) c[i] = (mask >> i) & 1;
    auto eval = [&](ll x) -> ll {
      ll res = c[0] - N;
      FOR(i, 1, K) {
        res = add(res, mult(c[i], power(x, i)));
      }
      return res;
    };

    ll lo = 0, hi = N+1;
    while (lo + 1 < hi) {
      ll mid = (lo + hi) / 2;
      if (eval(mid) <= 0) {
        lo = mid;
      }
      else {
        hi = mid;
      }
    }

    if (lo > 1 && eval(lo) == 0) {
      ans++;
    }
  }

  int b = 2;
  while (power(b, K) <= N) {
    ans += check(N, b);
    b++;
  }
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    ll N; cin >> N;
    solve(N);
  }
}

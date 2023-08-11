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

const int maxn = 1e6+6;
namespace Mobius {
  int mu[maxn];

  void mobius_sieve() {
    mu[1] = 1;
    for (int i = 1; i < maxn; i++) {
      for (int j = 2*i; j < maxn; j += i) {
        mu[j] -= mu[i];
      }
    }
  }
}
using Mobius::mu;

ll coprime[maxn];
ll count_coprime(int n) {
  if (coprime[n] != -1) return coprime[n];
  ll c = 0;
  for (int d = 1; d <= n; d++) {
    c += 1LL * mu[d] * (n / d) * (n / d);
  }
  c /= 2;
  return coprime[n] = c;
}

ll solve() {
  int N;
  ll M;
  cin >> N >> M;

  ll cost = M;
  for (int i = N/2; i >= 2; i--) {
    ll x = count_coprime(N / i);
    if (x >= i - 1) {
      ll take = min(M / (i - 1), x / (i - 1));
      ll use = take * (i - 1);
      M -= use;
      cost += take;
      if (M <= 0) return cost;
    }
  }

  if (M > 0) {
    return -1;
  }
  else return cost;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  memset(coprime, -1, sizeof coprime);
  Mobius::mobius_sieve();

  /*
  int N; cin >> N;

  map<ll, ll> vals;
  ll sum = 0;
  for (int i = 2; i <= N; i++) {
    ll x = count_coprime(N / i);
    if (x >= i-1) {
      ll use = (x / (i - 1)) * (i - 1);
      cout << i << ": " << use << endl;
      sum += use;
    }
  }
  DEBUG(sum);
  /*
  DEBUG(sz(vals));
  for (auto p: vals) {
    cout << p << endl;
  }
  */
  /*
  for (auto [x, c]: cnt) {
    cout << x << ": " << c << ": " << count_coprime(N/x) << '\n';
    vals.insert(c);
  }
  */
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}

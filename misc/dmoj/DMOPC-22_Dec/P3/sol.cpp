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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<ll> H(N);
  F0R(i, N) {
    cin >> H[i];
  }

  if (N == 2) {
    if (H[0] >= H[1]) {
      cout << H[0] + H[0] - H[1] << '\n';
    }
    else {
      cout << -1 << '\n';
    }
    return 0;
  }
  ll sum = std::accumulate(all(H), 0LL);

  auto check = [&](ll x) -> bool {
    if ((N * x - sum) % 3 != 0) {
      return false;
    }
    else {
      ll ops = (N * x - sum) / 3;
      ll extra = 0;
      F0Rd(i, N) {
        ll twos = min((x - H[i]) / 2, ops);
        ops -= twos;
        ll need = x - (H[i] + 2 * twos);
        if (need > extra) {
          return false;
        }
        else {
          extra -= need;
          extra += twos;
        }
      }
      return ops == 0 && extra == 0;
    }
  };

  auto md = [&](ll x, ll mx, ll step) -> ll {
    for (int i = 44; i >= 0; i--) {
      ll nx = x - (1LL << i) * step;
      if (mx <= nx && check(nx)) {
        x = nx;
      }
    }
    return x;
  };

  ll mx = *max_element(all(H));
  ll ans = 1e18;
  for (ll i = 1e13; i < 1e13 + 6; i++) {
    if (check(i)) {
      ckmin(ans, md(i, mx, N % 3 == 0 ? 2 : 6));
    }
  }

  cout << (ans < 1e18 ? ans : -1) << '\n';
}

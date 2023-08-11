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

ll solve(int tc) {
  int N, K, x; cin >> N >> K >> x;
  vector<ll> A(N+1), p(N+1);
  FOR(i, 1, N+1) {
    cin >> A[i];
  }
  if (x >= 0) {
    vector<ll> pfx(N+1);
    FOR(i, 1, N+1) {
      pfx[i] = A[i] + pfx[i-1];
    }
    p[0] = -x;
    FOR(i, 1, N+1) {
      p[i] = A[i] + p[i-1] - x;
    }
    ll ans = 0;
    ll mnPrefix = p[0];
    for (int i = 1; i <= N; i++) {
      for (int k = 1; k <= K && i-k >= 0; k++) {
        ckmax(ans, pfx[i] - pfx[i-k] + 1LL * k * x);
      }
      if (i-K >= 0) {
        ckmin(mnPrefix, p[i-K]);
        ckmax(ans, (p[i] + 2LL * K * x - mnPrefix));
      }
    }
    return ans;
  }
  else {
    vector<ll> pfx(N+1);
    FOR(i, 1, N+1) {
      pfx[i] = A[i] + pfx[i-1];
    }
    p[0] = -x;
    FOR(i, 1, N+1) {
      p[i] = A[i] + p[i-1] - x;
    }
    ll ans = 0;
    ll mnPrefix = p[0];
    for (int i = 1; N-i >= K; i++) {
      ckmax(ans, p[i] - mnPrefix);
      ckmin(mnPrefix, p[i]);
    }
    for (int i = N-K+1; i <= N; i++) {
      for (int j = 1; j <= i; j++) {
        int len = i - j + 1;
        if (N - len >= K) {
          ckmax(ans, pfx[i] - pfx[j-1] - 1LL * len * x);
        }
        else {
          int a = len - (N - K);
          int b = N - K;
          ckmax(ans, pfx[i] - pfx[j-1] + 1LL * a * x - 1LL * b * x);
        }
      }
    }
    return ans;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int t = 1; t <= T; t++) {
    cout << solve(t) << '\n';
  }
}

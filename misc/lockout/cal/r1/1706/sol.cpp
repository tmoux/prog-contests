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

ll solve() {
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  auto check = [&](int i) -> ll {
    ll mx = max(A[i-1], A[i+1]);
    if (A[i] < mx + 1) {
      return (mx + 1) - A[i];
    }
    else return 0LL;
  };

  const ll INF = 1e18;
  vector<ll> dpl(N, 0);
  vector<int> cntl(N, 0);
  for (int i = 1; i + 1 < N; i++) {
    dpl[i] = check(i) + (i-2 >= 0 ? dpl[i-2] : 0);
    cntl[i] = 1 + (i-2 >= 0 ? cntl[i-2] : 0);
  }
  vector<ll> dpr(N, 0);
  vector<int> cntr(N, 0);
  for (int i = N-2; i > 0; i--) {
    dpr[i] = check(i) + (i+2 < N ? dpr[i+2] : 0);
    cntr[i] = 1 + (i+2 < N ? cntr[i+2] : 0);
  }

  int target = N % 2 == 0 ? N/2 - 1 : N/2;
  ll ans = INF;
  F0R(i, N) {
    if (cntl[i] == target) {
      ckmin(ans, dpl[i]);
    }
    if (cntr[i] == target) {
      ckmin(ans, dpr[i]);
    }
  }
  F0R(i, N) {
    if (i + 3 < N) {
      int c = cntl[i] + cntr[i+3];
      if (c == target) {
        ckmin(ans, dpl[i] + dpr[i+3]);
      }
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}

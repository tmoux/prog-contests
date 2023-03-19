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

const int maxn = 10;
int N;
int A[maxn];
int B = 10;

void check() {
  bool p = true;
  F0R(mask, 1 << N) {
    if (__builtin_popcount(mask) == N / 2) {
      int sum = 0, prod = 1;
      F0R(i, N) {
        if (mask & (1 << i)) {
          sum += A[i];
        }
        else prod *= A[i];
      }
      if (sum != prod) {
        p = false;
        break;
      }
    }
  }
  if (p) {
    F0R(i, N) {
      cout << A[i] << ' ';
    }
    cout << endl;
  }
}

void rec(int i) {
  if (i == N) {
    check();
    return;
  }
  for (int x = -B; x <= B; x++) {
    A[i] = x;
    rec(i+1);
  }
}

void solve() {
  int N; cin >> N;
  N *= 2;
  vector<int> P(N);
  F0R(i, N) {
    cin >> P[i];
  }

  if (N == 2) {
    cout << abs(P[0] - P[1]) << '\n';
    return;
  }
  ll ans = 0;
  F0R(i, N) ans += abs(P[i]);
  if (N == 4) {
    ll tr = 0;
    F0R(i, N) tr += abs(P[i] - 2);
    ckmin(ans, tr);
  }
  if (N % 4 == 0) {
    ll tr = 0;
    F0R(i, N) tr += abs(P[i] - (-1));
    F0R(i, N) {
      tr -= abs(P[i] - (-1));
      tr += abs(P[i] - N/2);

      ckmin(ans, tr);

      tr -= abs(P[i] - N/2);
      tr += abs(P[i] - (-1));
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

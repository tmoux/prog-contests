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
  int N, K; cin >> N >> K;
  vector<ll> A(N+50);
  F0R(i, N+1) cin >> A[i];

  vector<int> B;
  ll carry = 0;
  F0R(i, N+50) {
    ll x = carry + A[i];
    int b = x&1;
    B.push_back(b);
    carry = (x - b) / 2;
  }
  if (carry == -1) {
    // flip
    F0R(i, N+1) {
      A[i] *= -1;
    }
    B.clear();
    carry = 0;
    F0R(i, N+50) {
      ll x = carry + A[i];
      int b = x&1;
      B.push_back(b);
      carry = (x - b) / 2;
    }
  }
  while (B.back() != 1) B.pop_back();

  int ans = 0;
  for (int i = 0; i <= N; i++) {
    if (sz(B)-i <= 40) {
      ll s = 0;
      for (int j = i; j < sz(B); j++) {
        s += (1LL * B[j]) << (j - i);
      }
      ll x = A[i] - s;
      if (abs(x) <= K && (i != N || x != 0)) ans++;
    }
    if (B[i] != 0) break;
  }
  cout << ans << '\n';
}

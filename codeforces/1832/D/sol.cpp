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
  int N, Q; cin >> N >> Q;
  vector<ll> A(N);
  F0R(i, N) cin >> A[i];
  sort(all(A));
  REP(Q) {
    int k; cin >> k;
    if (k <= N) {
      ll ans = 1e18;
      F0R(i, N) {
        if (i < k) ckmin(ans, A[i] + k-i);
        else ckmin(ans, A[i]);
      }
      cout << ans << ' ';
    }
    else {
      int dec = (k - N + 1) / 2;
      int inc = k - 2 * dec;
      vector<ll> B = A;
      F0R(i, inc) {
        B[i] += k-i;
      }
      sort(all(B));
      vector<ll> pfx(N);
      F0R(i, N) {
        pfx[i] = B[i];
        if (i > 0) pfx[i] += pfx[i-1];
      }
      ll lo = 0, hi = 3e9;
      // DEBUG(dec);
      // cout << B << endl;
      // cout << pfx << endl;
      while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        auto i = std::distance(B.begin(), lower_bound(all(B), mid));
        if (i >= N) hi = mid;
        else {
          ll sum = pfx[N-1] - (i == 0 ? 0 : pfx[i-1]) - mid * (N - i);
          if (sum >= dec) {
            lo = mid;
          }
          else hi = mid;
        }
      }

      cout << min(lo, B[0]) << ' ';
    }
  }
  cout << '\n';
}
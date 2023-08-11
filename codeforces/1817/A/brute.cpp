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

void solve() {
  int N, Q;
  cin >> N >> Q;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  vector<int> P(N);
  vector<int> increase;
  F0R(i, N) {
    if (i == 0 || A[i] > A[i-1]) {
      P[i] = 1;
      increase.push_back(i);
    }
    else if (i + 1 < N && A[i] < A[i+1]) P[i] = 1;
    if (i > 0) P[i] += P[i-1];
  }
  auto sum = [&](int l, int r) {
    return l == 0 ? P[r] : P[r] - P[l-1];
  };

  while (Q--) {
    int l, r; cin >> l >> r;
    l--, r--;
    int k = r-l+1;
    int ans = 0;
    auto get = [&](const vector<int>& v) {
      for (int i = 1; i + 1 < sz(v); i++) {
        if (v[i-1] >= v[i] && v[i] >= v[i+1]) return false;
      }
      return true;
    };
    F0R(mask, 1 << k) {
      vector<int> v;
      F0R(i, k) {
        if (mask & (1 << i)) {
          v.push_back(A[i+l]);
        }
      }
      if (get(v)) ckmax(ans, sz(v));
    }
    cout << ans << '\n';
    /*
    auto it = upper_bound(all(increase), r);
    assert(it != increase.begin());
    --it;
    // DEBUG(*it);
    if (*it < l) cout << min(2, r-l+1) << '\n';
    else {
      int ans = sum(l, *it);
      if (*it < r) ans++;
      cout << ans << '\n';
    }
    */
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T = 1;
  while (T--) solve();
}

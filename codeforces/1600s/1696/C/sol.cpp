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

bool solve() {
  int N, M; cin >> N >> M;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  int K; cin >> K;
  vector<int> B(K);
  F0R(i, K) {
    cin >> B[i];
  }

  auto make_vec = [&](vector<int> v) {
    vector<pair<int, int>> ret;
    for (auto x: v) {
      int mult = 1;
      while (x % M == 0) {
        mult *= M;
        x /= M;
      }
      ret.push_back({x, mult});
    }
    return ret;
  };

  auto check_same = [&](vector<pair<int, int>> a,
                        vector<pair<int, int>> b) -> bool {
    int i = 0, j = 0;
    int n = sz(a), m = sz(b);
    while (true) {
      if (i == n && j == m) return true;
      else if (i == n || j == m) return false;

      if (a[i].first == b[j].first) {
        int mn = min(a[i].second, b[j].second);
        a[i].second -= mn;
        b[j].second -= mn;

        if (i < n && a[i].second == 0) i++;
        if (j < m && b[j].second == 0) j++;
      }
      else return false;
    }
    assert(false);
  };

  auto As = make_vec(A);
  auto Bs = make_vec(B);
  return check_same(As, Bs);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << (solve() ? "Yes" : "No") << '\n';
  }
}

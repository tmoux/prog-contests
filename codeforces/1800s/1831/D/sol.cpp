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

// A[i] * A[j] = B[i] + B[j]
// B[i] = A[i] * A[j] - B[j]
void solve() {
  const int MAGIC = 800, M2 = 505;
  int N; cin >> N;
  vector<int> A(N), B(N);
  vector<vector<int>> mp(M2, vector<int>(N+1));
  F0R(i, N) cin >> A[i];
  F0R(i, N) cin >> B[i];
  F0R(i, N) {
    if (A[i] < M2) mp[A[i]][B[i]]++;
  }

  ll ans = 0;
  vector<int> cnt(N+1);
  FOR(x, 1, min(N+1, MAGIC)) {
    fill(all(cnt), 0);
    F0R(j, N) {
      ll y = 1LL * x * A[j] - B[j];
      if (0 < y && y <= N) cnt[y]++;
    }
    F0R(j, N) {
      if (A[j] == x) ans += cnt[B[j]];
    }
  }
  F0R(i, N) {
    if (A[i] >= MAGIC) {
      for (int x = 1; x <= N && 1LL * A[i] * x <= 2*N; x++) {
        int y = A[i] * x - B[i];
        if (0 < y && y <= N)
          ans += mp[x][y];
      }
    }
    if (1LL * A[i] * A[i] == B[i] + B[i]) ans--;
  }
  cout << ans/2 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

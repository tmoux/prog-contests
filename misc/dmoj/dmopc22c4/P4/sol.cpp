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
  int N, D; cin >> N >> D;
  vector<int> T(N);
  F0R(i, N) cin >> T[i];

  auto check = [&](int s, int i) -> int {
    int ans = 1;
    int c = s;
    int j = i;
    while (true) {
      while (j < N && T[j] < c + D) j++;
      if (j == N) break;
      if (T[j] >= c + 2 * D) break;
      else {
        ans++;
        c += D;
      }
    }
    c = s, j = i;
    while (true) {
      while (j >= 0 && T[j] >= c) j--;
      if (j < 0) break;
      if (T[j] < c - D) break;
      else {
        ans++;
        c -= D;
      }
    }
    return ans;
  };

  // SUB 1
  if (D == 1) {
    int ans = 0;
    int cur = 0;
    F0R(i, N) {
      if (i > 0 && T[i] == T[i-1] + 1) cur++;
      else if (i > 0 && T[i] == T[i-1]) cur = cur;
      else cur = 1;
      ckmax(ans, cur);
    }
    cout << ans << '\n';
  }
  else if (N <= 3000) {
    // SUB 2

    int ans = 0;
    F0R(i, N) {
      ckmax(ans, check(T[i], i));
    }
    cout << ans << '\n';
  }
  else {
    int ans = 0;
    int K = 15000;
    REP(K) {
      int i = rng() % N;
      ckmax(ans, check(T[i], i));
    }
    cout << ans << '\n';
  }
}

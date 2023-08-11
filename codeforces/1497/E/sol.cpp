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

const int maxn = 1e7+7;
int spf[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
      for (int j = i; j < maxn; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
}

void solve() {
  int N, K; cin >> N >> K;
  vector<int> A(N);
  F0R(i, N) {
    int x; cin >> x;
    int y = 1;
    while (x > 1) {
      int p = spf[x];
      int c = 0;
      while (x % p == 0) {
        x /= p;
        c ^= 1;
      }
      if (c) y *= p;
    }
    A[i] = y;
  }

  map<int, vector<int>> mp;
  vector<int> left(N, -1);
  F0R(i, N) mp[A[i]].push_back(i);
  for (auto [x, v]: mp) {
    for (int i = 1; i < sz(v); i++) {
      left[v[i]] = v[i-1];
    }
  }
  set<int> S;
  set<int> seen;
  F0Rd(i, N) {
    if (seen.count(A[i])) {
      S.insert(i);
    }
    else seen.insert(A[i]);
  }

  vector<vector<int>> Prev(N, vector<int>(K+1));
  F0Rd(i, N) {
    auto it = S.rbegin();
    F0R(k, K+1) {
      if (it != S.rend()) {
        Prev[i][k] = *it;
        ++it;
      }
      else {
        Prev[i][k] = -1;
      }
    }
    if (left[i] != -1) {
      assert(S.count(left[i]));
      S.erase(left[i]);
    }
  }

  vector<vector<int>> dp(N, vector<int>(K+1, N));
  F0R(i, N) {
    for (int k = 0; k <= K; k++) {
      for (int l = 0; l <= k; l++) {
        int j = Prev[i][l];
        ckmin(dp[i][k], (j == -1 ? 0 : dp[j][k-l]) + 1);
      }
    }
  }
  cout << dp[N-1][K] << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  int T; cin >> T;
  while (T--) solve();
}

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

int solve() {
  int N; cin >> N;
  vector<vector<int>> adj(N);
  REP(N-1) {
    int a, b; cin >> a >> b; a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<pair<int, int>> dp(N);
  // Compute DP initially.

  auto getp = [](const multiset<int>& paths, const multiset<int>& mns) -> pair<int, int> {
    assert(sz(paths) == sz(mns));
    if (paths.empty()) {
      return {1, 1e9};
    }
    else if (sz(paths) == 1) {
      return {*paths.begin() + 1, *mns.begin()};
    }
    else {
      return {*paths.begin() + 1, min(*next(paths.begin()), *mns.begin())};
    }
  };

  auto dfs = y_combinator([&](auto dfs, int i, int p) -> void {
    multiset<int> paths, mns;
    for (int j: adj[i]) {
      if (j == p) continue;
      dfs(j, i);
      paths.insert(dp[j].first);
      mns.insert(dp[j].second);
    }
    dp[i] = getp(paths, mns);
    // cout << i << ": " << dp[i] << endl;
  });
  dfs(0, 0);

  auto getans = [&getp](const multiset<int>& paths, const multiset<int>& mns) -> int {
    auto p = getp(paths, mns);
    return min(p.first, p.second);
  };

  int ans = 0;
  // Compute DP rerooting.
  auto reroot = y_combinator([&](auto reroot, int i, int p, pair<int, int> par) -> void {
    multiset<int> paths, mns;
    if (i != p) {
      paths.insert(par.first);
      mns.insert(par.second);
    }
    for (int j: adj[i]) {
      if (j == p) continue;
      paths.insert(dp[j].first);
      mns.insert(dp[j].second);
    }
    ckmax(ans, getans(paths, mns));

    for (int j: adj[i]) {
      if (j == p) continue;
      auto it = paths.find(dp[j].first);
      paths.erase(it);
      it = mns.find(dp[j].second);
      mns.erase(it);

      reroot(j, i, getp(paths, mns));

      paths.insert(dp[j].first);
      mns.insert(dp[j].second);
    }
  });
  reroot(0, 0, make_pair(-1, -1));
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}

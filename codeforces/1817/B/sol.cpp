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
  int N, M; cin >> N >> M;
  vector<vector<int>> adj(N);
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  auto poss = [&](int R) -> bool {
    set<int> s;
    for (int j: adj[R]) {
      s.insert(j);
    }
    vector<bool> vis(N);
    bool found = false;
    vector<int> st;
    vector<pair<int, int>> ans;
    auto dfs = y_combinator([&](auto dfs, int i, int p) -> void {
      st.push_back(i);
      vis[i] = 1;
      bool hasCyc = false;
      bool addBack = false;
      if (s.count(i)) {
        addBack = true;
        s.erase(i);
      }
      for (int j: adj[i]) {
        if (j == p) continue;
        else if (j == R) hasCyc = true;
      }
      if (hasCyc && sz(s) >= 2) {
        found = true;
        assert(sz(st) >= 2);
        ans.clear();
        for (int i = 0; i + 1 < sz(st); i++) {
          ans.push_back({st[i], st[i+1]});
        }
        ans.push_back({R, st.back()});
        ans.push_back({R, *s.begin()});
        ans.push_back({R, *next(s.begin())});
      }
      for (int j: adj[i]) {
        if (j == p) continue;
        else if (j == R) hasCyc = true;
        else if (vis[j]) continue;
        else {
          dfs(j, i);
        }
      }

      if (addBack) s.insert(i);
      st.pop_back();
    });
    dfs(R, R);
    if (found) {
      cout << "YES\n";
      cout << sz(ans) << '\n';
      for (auto [a, b]: ans) {
        cout << a+1 << ' ' << b+1 << '\n';
      }
      return true;
    }
    return false;
  };
  F0R(i, N) {
    if (poss(i)) {
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

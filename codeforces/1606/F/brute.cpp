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

const int maxn = 2e5+5;
int N;
vector<int> adj[maxn];
vector<int> ch[maxn];

void dfs(int i, int p) {
  for (int j: adj[i]) {
    if (j == p) continue;
    dfs(j, i);
    ch[i].push_back(j);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  REP(N-1) {
    int x, y; cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(1, 1);

  auto query = [&](int v, int k) -> int {
    auto dfs = y_combinator([&](auto dfs, int i) -> int {
      int tr = -k;
      for (int j: ch[i]) {
        tr += dfs(j);
      }
      return max(1, tr);
    });

    return dfs(v);
  };

  auto DFS = y_combinator([&](auto DFS, int i) -> void {
    for (int j: ch[i]) {
      DFS(j);
    }
    cout << i << ": ";
    F0R(k, 10) {
      cout << -query(i, k) << ' ';
    }
    cout << endl;
  });

  //DFS(1);
  //return 0;

  int Q; cin >> Q;
  while (Q--) {
    int v, k; cin >> v >> k;
    int ans = 0;
    for (int j: ch[v]) ans += query(j, k);
    cout << ans << '\n';
  }
}

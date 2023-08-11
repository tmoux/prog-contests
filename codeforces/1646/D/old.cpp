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
vector<int> c[2];

void dfs(int i, int p, int color) {
  c[color].push_back(i);
  for (int j: adj[i]) {
    if (j != p) {
      dfs(j, i, color^1);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs(1, 1, 0);

  auto check = [&]() -> tuple<int, int, vector<int>> {
    vector<int> ans(N+1);
    for (auto i: c[0]) ans[i] = sz(adj[i]);
    for (auto i: c[1]) ans[i] = 1;
    int sum = std::accumulate(ans.begin() + 1, ans.begin() + N + 1, 0);
    int tot = sz(c[0]);
    for (auto i: c[1]) if (sz(adj[i]) == 1 && ans[adj[i][0]] == 1) tot++;

    return {tot, sum, ans};
  };

  auto [t1, s1, ans1] = check();
  swap(c[0], c[1]);
  auto [t2, s2, ans2] = check();

  if (t1 < t2 || (t1 == t2 && s1 > s2)) {
    swap(t1, t2);
    swap(s1, s2);
    swap(ans1, ans2);
  }

  cout << t1 << ' ' << s1 << '\n';
  FOR(i, 1, N+1) {
    cout << ans1[i] << ' ';
  }
  cout << '\n';
}

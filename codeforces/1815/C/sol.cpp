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
  vector<vector<int>> g(N), gr(N);
  vector<int> indegree(N);
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    g[b].push_back(a);
    gr[a].push_back(b);
  }

  queue<int> q;
  q.push(0);
  const int INF = 1e9;
  vector<int> maxNodes(N, INF);
  maxNodes[0] = 1;
  vector<vector<int>> V(N+1);
  while (!q.empty()) {
    int i = q.front(); q.pop();
    V[maxNodes[i]].push_back(i);
    // cout << i << ": " << maxNodes[i] << endl;
    for (auto j: g[i]) {
      if (maxNodes[j] > maxNodes[i] + 1) {
        maxNodes[j] = maxNodes[i] + 1;
        q.push(j);
      }
    }
  }
  F0R(i, N) {
    if (maxNodes[i] == INF) {
      cout << "INFINITE" << '\n';
      return;
    }
  }

  vector<int> ans;
  int B = *max_element(all(maxNodes));
  for (int i = B-1; i >= 1; i--) {
    for (auto x: V[B]) {
      ans.push_back(x);
    }
    for (int j = i; j < B; j++) {
      for (auto x: V[j]) {
        ans.push_back(x);
      }
    }
  }
  for (auto x: V[B]) {
    ans.push_back(x);
  }

  cout << "FINITE" << '\n';
  cout << sz(ans) << '\n';
  for (auto x: ans) {
    cout << x+1 << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

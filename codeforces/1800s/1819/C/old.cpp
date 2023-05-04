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

bool isLeaf(int i) {
  return sz(adj[i]) == 1;
}

bool dfs(int i, int p, bool rev, vector<int>& v) {
  vector<int> leafs, t1s;
  for (int j: adj[i]) {
    if (j == p) continue;
    if (isLeaf(j)) leafs.push_back(j);
    else t1s.push_back(j);
  }

  if (sz(t1s) > 1) return false;
  else {
    if (!rev) {
      for (int j: leafs) v.push_back(j);
      if (sz(t1s) == 1) {
        bool b = dfs(t1s[0], i, true, v);
        if (!b) return false;
      }
      v.push_back(i);
    }
    else {
      v.push_back(i);
      if (sz(t1s) == 1) {
        bool b = dfs(t1s[0], i, false, v);
        if (!b) return false;
      }
      for (int j: leafs) v.push_back(j);
    }
    return true;
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
  if (N == 2) {
    cout << "Yes\n";
    cout << 1 << ' ' << 2 << '\n';
    return 0;
  }

  vector<vector<int>> dist(N+1, vector<int>(N + 1, maxn));
  FOR(i, 1, N+1) {
    queue<int> q;
    dist[i][i] = 0;
    q.push(i);
    while (!q.empty()) {
      int f = q.front(); q.pop();
      for (int j: adj[f]) {
        if (dist[i][j] > dist[i][f] + 1) {
          dist[i][j] = dist[i][f] + 1;
          q.push(j);
        }
      }
    }
  }

  auto checkNo = [&]() {
    vector<int> p(N); iota(all(p), 1);
    do {
      bool poss = true;
      F0R(i, N) {
        int u = p[i], v = p[(i+1)%N];
        if (dist[u][v] > 2) poss = false;
      }
      if (poss) {
        cout << "FOUND " << p << endl;
        assert(false);
      }
    } while (next_permutation(all(p)));
  };

  // top level
  vector<int> leafs;
  vector<vector<int>> t1s;
  int R = 1;
  while (isLeaf(R)) R++;
  for (int j: adj[R]) {
    if (isLeaf(j)) leafs.push_back(j);
    else {
      vector<int> v;
      bool b = dfs(j, R, false, v);
      if (b) {
        t1s.push_back(v);
      }
      else {
        cerr << "fail on " << j << endl;
        cerr << "No" << '\n';
        checkNo();
        cerr << "Correct " << endl;
        return 0;
      }
    }
  }

  if (sz(t1s) <= 2) {
    vector<int> ans = {R};
    if (sz(t1s) > 1) {
      for (auto x: t1s[0]) {
        ans.push_back(x);
      }
    }
    for (auto x: leafs) ans.push_back(x);
    if (sz(t1s) > 0) {
      reverse(all(t1s.back()));
      for (auto x: t1s.back()) {
        ans.push_back(x);
      }
    }


    cout << "Yes" << '\n';
    for (auto x: ans) {
      cout << x << ' ';
    }
    cout << '\n';
    cout << endl;

    F0R(i, sz(ans)) {
      int u = ans[i], v = ans[(i+1)%N];
      assert(dist[u][v] <= 2);
    }
  }
  else {
    cout << "No\n";
    checkNo();
    cerr << "Correct " << endl;
  }
}

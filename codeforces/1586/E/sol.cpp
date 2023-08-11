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

const int maxn = 3e5+5;
vector<int> adj[maxn];
int N, M, Q;
int in[maxn], out[maxn];

vector<int> find_path(int a, int b) {
  vector<int> prev(N+1, -1);
  queue<int> q;
  q.push(a); prev[a] = a;
  while (!q.empty()) {
    int i = q.front(); q.pop();
    if (i == b) {
      vector<int> path;
      while (1) {
        path.push_back(i);
        if (i == a) break;
        i = prev[i];
      }
      return path;
    }
    for (int j: adj[i]) {
      if (prev[j] == -1) {
        prev[j] = i;
        q.push(j);
      }
    }
  }
  assert(false);
}

vector<int> ans[maxn];

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  DSU dsu(N);
  REP(M) {
    int a, b; cin >> a >> b;
    if (dsu.Find(a) != dsu.Find(b)) {
      adj[a].push_back(b);
      adj[b].push_back(a);
      dsu.Union(a, b);
    }
  }
  cin >> Q;

  F0R(i, Q) {
    int a, b; cin >> a >> b;
    in[a]++, in[b]++;

    ans[i] = find_path(a, b);
  }

  int num_add = 0;
  FOR(i, 1, N+1) {
    num_add += in[i]&1;
  }
  if (num_add > 0) {
    cout << "NO\n";
    assert(num_add % 2 == 0);
    cout << num_add / 2 << '\n';
  }
  else {
    cout << "YES\n";
    F0R(i, Q) {
      cout << sz(ans[i]) << '\n';
      reverse(all(ans[i]));
      for (auto x: ans[i]) {
        cout << x << ' ';
      }
      cout << '\n';
    }
  }
}

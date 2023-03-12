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

struct DSU {
  int n;
  vector<int> par;
  vector<int> edges;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
    edges.resize(n+1, 0);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { //return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) {
      edges[x]++;
      return false;
    }
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    edges[x] += edges[y] + 1;
    return true;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;

  DSU dsu(N);
  F0R(i, M) {
    int a;
    char b;
    int c;
    char d;
    cin >> a >> b >> c >> d;

    dsu.Union(a, c);
  }

  int X = 0, Y = 0;
  set<int> s;
  FOR(i, 1, N+1) {
    // cout << i << ": " << -dsu.par[dsu.Find(i)] << endl;
    int I = dsu.Find(i);
    if (!s.count(I)) {
      s.insert(I);
      int sz = -dsu.par[I];
      if (dsu.edges[I] == sz) X++;
      else Y++;

      // cout << I << " " << sz << ' ' << dsu.edges[I] << endl;
    }
  }

  cout << X << ' ' << Y << '\n';
}

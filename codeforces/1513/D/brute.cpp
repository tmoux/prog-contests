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

  int getsz(int i) {
    return -par[Find(i)];
  }
};

void solve() {
  int N, P; cin >> N >> P;
  vector<int> A(N);
  vector<int> v;
  map<int, vector<int>> mp;
  F0R(i, N) {
    cin >> A[i];
    v.push_back(A[i]);
    mp[A[i]].push_back(i);
  }

  vector<array<int, 3>> edges;
  F0R(i, N) {
    if (i + 1 < N) {
      edges.push_back({P, i, i+1});
    }
    FOR(j, i+1, N) {
      if (A[j] % A[i] != 0) break;
      edges.push_back({A[i], i, i+1});
    }
  }
  sort(all(v)); v.erase(unique(all(v)), v.end());

  DSU dsu(N);
  ll ans = 0;
  for (auto x: v) {
    if (x > P) break;
    for (auto i: mp[x]) {
      if (dsu.getsz(i) > 1) continue;
      for (int j = i+1; j < N; j++) {
        if (A[j] % A[i] != 0) break;
        if (dsu.Find(i) != dsu.Find(j)) {
          dsu.Union(i, j);
          ans += x;
        }
      }
    }
  }

  F0R(i, N-1) {
    if (dsu.Find(i) != dsu.Find(i+1)) {
      dsu.Union(i, i+1);
      ans += P;
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

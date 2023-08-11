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

  bool isConnected(int x, int y) {
    return Find(x) == Find(y);
  }
};

void solve() {
  int N, M, Q; cin >> N >> M >> Q;
  vector<pair<int, int>> edges(M);
  F0R(i, M) {
    int a, b; cin >> a >> b;
    edges[i] = {a, b};
  }

  vector<pair<int, int>> queries(Q);
  vector<int> ans(Q);
  using T = tuple<int, int, vector<int>>;
  vector<T> V;
  V.push_back({0, M, {}});
  F0R(i, Q) {
    int l, r; cin >> l >> r;
    queries[i] = {l, r};
    get<2>(V[0]).push_back(i);
  }

  while (!V.empty()) {
    map<pair<int, int>, vector<int>> nV;
    DSU dsu(N);

    vector<int> R(N+1); iota(all(R), 0);
    auto getR = y_combinator([&](auto getR, int i) -> int {
      if (R[i] == N) return N;
      if (dsu.isConnected(R[i], R[i]+1)) {
        return R[i] = getR(R[i]+1);
      }
      else return R[i];
    });

    int k = 0;
    for (auto [L, R, v]: V) {
      // cout << L << ' ' << R << ' ' << v << endl;
      if (L == R) {
        for (int i: v) {
          ans[i] = L;
        }
      }
      else {
        int m = (L + R) / 2;
        while (k < m) {
          auto [a, b] = edges[k++];
          dsu.Union(a, b);
        }
        for (int i: v) {
          auto [l, r] = queries[i];
          if (getR(l) >= r) {
            nV[{L, m}].push_back(i);
          }
          else {
            nV[{m+1, R}].push_back(i);
          }
        }
      }
    }

    V.clear();
    for (auto [p, v]: nV) {
      V.push_back({p.first, p.second, v});
    }
  }

  F0R(i, Q) {
    cout << ans[i] << " \n"[i == Q-1];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

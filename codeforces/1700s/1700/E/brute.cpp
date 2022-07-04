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
  int comps;
  DSU(int _n) {
    n = _n;
    par.resize(n, -1);
    comps = n;
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // returns true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    comps--;
    return true;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<vector<int>> A(N, vector<int>(M));
  vector<array<int, 2>> pos(N*M);
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j]; --A[i][j];
      pos[A[i][j]] = {i, j};
    }
  }

  auto check = [&]() -> bool {
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {1, 0, -1, 0};
    vector<array<int, 2>> pos(N*M);
    F0R(i, N) F0R(j, M) {
      pos[A[i][j]] = {i, j};
    }

    DSU dsu(N*M);
    F0R(x, N*M) {
      auto [i, j] = pos[x];
      F0R(k, 4) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (0 <= ni && ni < N && 0 <= nj && nj < M && A[ni][nj] < x) {
          dsu.Union(x, A[ni][nj]);
        }
      }
      if (dsu.comps != N*M - x) return false;
    }
    return true;
  };

  if (check()) {
    cout << 0 << '\n';
  }
  else {
    int ans = 0;
    for (int x = 0; x < N*M; x++) {
      for (int y = x+1; y < N*M; y++) {
        auto [i1, j1] = pos[x];
        auto [i2, j2] = pos[y];
        swap(A[i1][j1], A[i2][j2]);
        if (check()) {
          // cout << x+1 << ' ' << y+1 << endl;
          ans++;
        }
        swap(A[i1][j1], A[i2][j2]);
      }
    }
    if (ans > 0) {
      cout << 1 << ' ' << ans << '\n';
    }
    else cout << 2 << '\n';
  }
}

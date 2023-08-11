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

struct DSU { // {{{
  int n;
  using va = array<set<int>, 2>;
  vector<va*> par;

  DSU(int _n) {
    n = _n;
    par.resize(n);
    F0R(i, n) {
      par[i] = new array<set<int>, 2>;
      (*(par[i]))[0].insert(i);
    }
  }

  int color(int i) {
    return (*par[i])[0].count(i) ? 0 : 1;
  }

  int size(va& u) {
    return sz(u[0]) + sz(u[1]);
  }

  void merge(va& u, va& v, bool flip = false) {
    if (sz(u) < sz(v)) swap(u, v);
    if (flip) swap(u[0], u[1]);

    F0R(k, 2) {
      for (auto x: v[k]) {
        u[k].insert(x);
        par[x] = &u;
      }
    }
  }

  void make_diff(int i, int j) {
    auto u = par[i];
    auto v = par[j];

    if (u != v) {
      int ci = color(i);
      int cj = color(j);
      merge(*u, *v, ci == cj);
    }
  }

  void make_same(int i, int j) {
    auto u = par[i];
    auto v = par[j];

    if (u != v) {
      int ci = color(i);
      int cj = color(j);
      merge(*u, *v, ci != cj);
    }
  }

  vector<int> get_ops() {
    set<va*> s;
    F0R(i, n) {
      s.insert(par[i]);
    }

    vector<int> ret;
    for (auto v: s) {
      for (auto x: (*v)[0]) {
        ret.push_back(x);
      }
    }
    return ret;
  }
}; // }}}

void solve() {
  int N; cin >> N;
  vector<vector<int>> A(N, vector<int>(N));
  F0R(i, N) {
    F0R(j, N) {
      cin >> A[i][j];
    }
  }

  DSU dsu(N);
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (A[i][j] > A[j][i]) {
        dsu.make_diff(i, j);
      }
      else if (A[i][j] < A[j][i]) {
        dsu.make_same(i, j);
      }
    }
  }

  auto op = [&](int x) {
    F0R(i, N) {
      swap(A[i][x], A[x][i]);
    }
  };

  auto ops = dsu.get_ops();
  for (auto x: ops) op(x);

  F0R(i, N) {
    F0R(j, N) {
      cout << A[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}

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

const int maxn = 105;
int N, M, K, C[maxn];

int diameter(vector<vector<int>> g) {
  int n = sz(g);
  vector<vector<int>> d(n, vector<int>(n, 1e9));
  F0R(i, n) d[i][i] = 0;
  F0R(i, n) {
    F0R(j, n) {
      if (g[i][j]) d[i][j] = 1;
    }
  }

  F0R(k, n) {
    F0R(i, n) {
      F0R(j, n) {
        ckmin(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }

  int diam = 0;
  F0R(i, n) {
    F0R(j, n) {
      if (i != j) {
        if (d[i][j] < 1e9) ckmax(diam, d[i][j]);
      }
    }
  }
  return diam;
}

pair<vector<vector<int>>, vector<int>> iter(vector<vector<int>> g, vector<int> c) {
  int n = sz(g);
  vector<int> nc(2*n);
  vector<vector<int>> ng(2*n, vector<int>(2*n));
  F0R(i, n) nc[2*i] = nc[2*i+1] = c[i];
  F0R(i, n) ng[2*i][2*i+1] = ng[2*i+1][2*i] = 1;
  F0R(i, n) {
    F0R(j, n) {
      if (g[i][j]) {
        if (c[i] == c[j]) {
          ng[2*i][2*j] = ng[2*j][2*i] = 1;
          ng[2*i+1][2*j+1] = ng[2*j+1][2*i+1] = 1;
        }
        else {
          ng[2*i][2*j+1] = ng[2*j+1][2*i] = 1;
          ng[2*i+1][2*j] = ng[2*j][2*i+1] = 1;
        }
      }
    }
  }
  return {ng, nc};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> K;
  vector<int> c(N);
  F0R(i, N) cin >> c[i];
  vector<vector<int>> g(N, vector<int>(N));
  F0R(i, M) {
    int a, b; cin >> a >> b; a--, b--;
    g[a][b] = g[b][a] = 1;
  }

  DEBUG(diameter(g));
  F0R(i, K) {
    std::tie(g, c) = iter(g, c);
    F0R(j, sz(g)) {
      // cout << g[j] << endl;
    }
    cout << "iter " << i+1 << ": " << diameter(g) << endl;
  }
}

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
  private:
    int N, M;
    int n;
    int comps = 0;
    vector<int> par;
    vector<vector<int>> on;

    int cv(int i, int j) {
      return i * M + j;
    }
    bool valid(int i, int j) {
      return 0 <= i && i < N && 0 <= j && j < M;
    }

    int Find(int i) {
      return par[i] < 0 ? i : par[i] = Find(par[i]);
    }

    bool Union(int x, int y) { // return true if x and y were not connected
      x = Find(x);
      y = Find(y);
      if (x == y) return false;
      comps--;
      if (par[x] > par[y]) swap(x, y);
      par[x] += par[y];
      par[y] = x;
      return true;
    }

  public:
    DSU(int _N, int _M) : N(_N), M(_M) {
      par.resize(N*M, -1);
      on = vector<vector<int>>(N, vector<int>(M));
    }

    void add_vertex(int i, int j) {
      on[i][j] = 1;
      comps++;
      int dx[] = {0, 1, 0, -1};
      int dy[] = {1, 0, -1, 0};
      F0R(k, 4) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (valid(ni, nj) && on[ni][nj]) {
          Union(cv(i, j), cv(ni, nj));
        }
      }
    }

    int getComps() const {
      return comps;
    }
};

const int maxn = 305, maxq = 2e6+6;
int N, M, Q;

using T = array<int, 3>;
vector<T> adds[maxq], removes[maxq];
int A[maxn][maxn];

int ans[maxq];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> Q;
  F0R(i, N) F0R(j, M) adds[0].push_back({i, j, 0});
  int mxc = 0;
  FOR(i, 1, Q+1) {
    int x, y, c; cin >> x >> y >> c;
    ckmax(mxc, c);
    x--, y--;
    if (A[x][y] != c) {
      removes[A[x][y]].push_back({x, y, i});
      A[x][y] = c;
      adds[A[x][y]].push_back({x, y, i});
    }
  }

  for (int c = 0; c <= mxc; c++) {
    {
      DSU dsu(N, M);
      F0R(idx, sz(adds[c])) {
        auto [x, y, i] = adds[c][idx];
        dsu.add_vertex(x, y);
        int comps = dsu.getComps();
        if (idx + 1 < sz(adds[c])) {
          int j = adds[c][idx+1][2];
          if (i < j) {
            ans[i] += comps;
            ans[j] -= comps;
            // printf("+ %d on [%d, %d]\n", comps, i, j-1);
          }
        }
        else if (idx == sz(adds[c]) - 1) {
          int j = removes[c].empty() ? Q + 1 : removes[c][0][2];
          ans[i] += comps;
          ans[j] -= comps;
          // printf("+ %d on [%d, %d]\n", comps, i, j-1);
        }
      }
    }
    {
      DSU dsu = DSU(N, M);
      F0R(i, N) F0R(j, M) {
        if (A[i][j] == c) dsu.add_vertex(i, j);
      }
      int j = Q+1;
      F0Rd(idx, sz(removes[c])) {
        auto [x, y, i] = removes[c][idx];
        int comps = dsu.getComps();
        ans[i] += comps;
        ans[j] -= comps;
        // printf("+ %d on [%d, %d]\n", comps, i, j-1);
        dsu.add_vertex(x, y);
        j = i;
      }
    }
  }

  for (int i = 1; i <= Q; i++) {
    ans[i] += ans[i-1];
    cout << ans[i] << '\n';
  }
}

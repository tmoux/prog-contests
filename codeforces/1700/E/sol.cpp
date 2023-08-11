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
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j]; --A[i][j];
    }
  }

  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {1, 0, -1, 0};
  vector<set<int>> neighbors(N*M);
  F0R(i, N) F0R(j, M) {
    int x = A[i][j];
    F0R(k, 4) {
      int ni = i + dx[k];
      int nj = j + dy[k];
      if (0 <= ni && ni < N && 0 <= nj && nj < M) {
        neighbors[x].insert(A[ni][nj]);
      }
    }
  }

  vector<int> cnt(N*M, 0);
  vector<bool> valid(N*M, false);
  int inv = 0;
  F0R(x, N*M) {
    valid[x] = x == 0 || *neighbors[x].begin() < x;
    if (!valid[x]) {
      inv++;
      for (auto y: neighbors[x]) cnt[y]++;
    }
  }
  if (inv == 0) {
    cout << 0 << '\n';
  }
  else {
    vector<bool> S(N*M, false);
    {
      DSU dsu(N*M);
      F0R(x, N*M) {
        for (int y: neighbors[x]) if (y < x) {
          dsu.Union(x, y);
        }
        S[x] = dsu.comps == N*M - x;
      }
    }
    int Rmin = N*M-1;
    while (S[Rmin]) Rmin--;
    vector<int> Rs;
    F0R(x, N*M) if (cnt[x] == inv && Rmin < x) Rs.push_back(x);

    int ans = 0;
    for (int L = 0; L == 0 || valid[L-1]; L++) {
      vector<int>& candidates = Rs;
      if (!valid[L]) {
        vector<int> nrs;
        vector<int> mycnt(N*M, 0);
        F0R(x, N*M) {
          if (x == L) continue;
          if (!valid[x]) {
            for (auto y: neighbors[x]) mycnt[y]++;
          }
        }
        F0R(x, N*M) {
          if (mycnt[x] == inv-1 && Rmin < x) nrs.push_back(x);
        }
        candidates = nrs;
      }
      for (int R: candidates) {
        // if (!valid[L] && *neighbors[R].begin() >= L) continue;
        if (L == 0 || *neighbors[R].begin() < L) {
          bool poss = true;
          for (int x: neighbors[L]) {
            if (L < x && x < R) {
              int min_neighbor = 2e9;
              for (auto y: neighbors[x]) {
                if (y != L) ckmin(min_neighbor, y);
              }
              poss &= min_neighbor < x || neighbors[x].count(R);
            }
          }
          if (poss) {
            ans++;
          }
        }
      }
    }

    if (ans > 0) {
      cout << 1 << ' ' << ans << '\n';
    }
    else cout << 2 << '\n';
  }
}

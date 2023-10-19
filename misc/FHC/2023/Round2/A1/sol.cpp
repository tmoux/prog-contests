#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

bool solve() {
  int N, M; cin >> N >> M;
  vector<string> G(N);
  F0R(i, N) cin >> G[i];
  DSU dsu(N*M);
  auto cv = [&](int i, int j) -> int {
    return i * M + j;
  };
  auto valid = [&](int i, int j) -> bool {
    return 0 <= i && i < N && 0 <= j && j < M;
  };

  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {1, 0, -1, 0};
  F0R(i, N) {
    F0R(j, M) {
      if (G[i][j] == 'W') {
        F0R(k, 4) {
          int ni = i + dx[k];
          int nj = j + dy[k];
          if (valid(ni, nj) && G[ni][nj] == 'W') {
            dsu.Union(cv(i, j), cv(ni, nj));
          }
        }
      }
    }
  }

  vector<vector<int>> spaces(N*M);
  F0R(i, N) {
    F0R(j, M) {
      if (G[i][j] == 'W') {
        F0R(k, 4) {
          int ni = i + dx[k];
          int nj = j + dy[k];
          if (valid(ni, nj) && G[ni][nj] == '.') {
            spaces[dsu.Find(cv(i, j))].push_back(cv(ni, nj));
          }
        }
      }
    }
  }

  vector<int> cnt(N*M);
  F0R(i, N) {
    F0R(j, M) {
      int c = cv(i, j);
      if (c == dsu.Find(c)) {
        int comp_size = -dsu.par[c];
        sort(all(spaces[c])); spaces[c].erase(unique(all(spaces[c])), spaces[c].end());
        if (sz(spaces[c]) == 1) {
          cnt[spaces[c][0]] += comp_size;
        }
      }
    }
  }

  return *max_element(all(cnt)) > 0;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tc, 1, T+1) {
    cout << "Case #" << tc << ": " << (solve() ? "YES" : "NO") << '\n';
  }

}

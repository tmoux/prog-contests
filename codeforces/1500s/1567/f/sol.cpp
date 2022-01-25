#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
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
// }}}

const int maxn = 505;
int n, m;
char grid[maxn][maxn];

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

bool valid(int i, int j) {
  return 0 <= i && i < n && 0 <= j && j < m;
}

int cv(int i, int j) {
  return i * m + j;
}

vector<int> adj[maxn*maxn];
int color[maxn*maxn];

void dfs(int i, int c = 0) {
  color[i] = c;
  for (int j: adj[i]) {
    if (color[j] != -1) {
      assert(color[j] ^ color[i]);
    }
    else {
      dfs(j, c^1);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m;
  F0R(i, n) {
    F0R(j, m) {
      cin >> grid[i][j];
    }
  }

  bool poss = true;
  F0R(i, n) {
    F0R(j, m) {
      if (grid[i][j] == 'X') {
        vector<int> v;
        for (int k = 0; k < 4; k++) {
          int ni = i + dx[k];
          int nj = j + dy[k];
          if (grid[ni][nj] == '.') 
            v.push_back(cv(ni, nj));
        }
        if (sz(v)&1) poss = false;
        else if (sz(v) == 2) {
          adj[v[0]].push_back(v[1]);
          adj[v[1]].push_back(v[0]);
        }
        else if (sz(v) == 4) {
          adj[v[0]].push_back(v[1]);
          adj[v[1]].push_back(v[0]);

          adj[v[2]].push_back(v[3]);
          adj[v[3]].push_back(v[2]);
        }
      }
    }
  }
  if (!poss) {
    cout << "NO\n";
  }
  else {
    memset(color, -1, sizeof color);
    F0R(i, n*m) if (color[i] == -1) dfs(i);

    vector<vector<int>> ans(n, vector<int>(m));
    F0R(i, n) {
      F0R(j, m) {
        if (grid[i][j] != 'X') {
          ans[i][j] = color[cv(i, j)] == 0 ? 1 : 4;
        }
      }
    }
    F0R(i, n) {
      F0R(j, m) {
        if (grid[i][j] == 'X') {
          for (int k = 0; k < 4; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            if (grid[ni][nj] == '.') ans[i][j] += ans[ni][nj];
          }
        }
      }
    }

    cout << "YES\n";
    F0R(i, n) {
      F0R(j, m) {
        cout << ans[i][j] << ' ';
      }
      cout << '\n';
    }
  }
}

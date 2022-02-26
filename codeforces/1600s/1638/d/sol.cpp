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

const int maxn = 1005;
int n, m;
int c[maxn][maxn];
bool vis[maxn][maxn];

bool valid(int i, int j) {
  return 0 <= i && i < n && 0 <= j && j < m;
}

int canStamp(int i, int j) {
  if (0 <= i && i < n-1 && 0 <= j && j < m-1) {
    set<int> colors;
    if (c[i][j] != -1) colors.insert(c[i][j]);
    if (c[i+1][j] != -1) colors.insert(c[i+1][j]);
    if (c[i][j+1] != -1) colors.insert(c[i][j+1]);
    if (c[i+1][j+1] != -1) colors.insert(c[i+1][j+1]);

    if (sz(colors) == 1) return *colors.begin();
    else return -1;
  }
  else return -1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m;
  F0R(i, n) {
    F0R(j, m) {
      cin >> c[i][j];
    }
  }

  queue<array<int, 3>> q;
  F0R(i, n) {
    F0R(j, m) {
      int color = canStamp(i, j);
      if (color != -1) {
        vis[i][j] = true;
        q.push({i, j, color});
      }
    }
  }

  vector<array<int,3>> ans;
  while (!q.empty()) {
    auto [i, j, color] = q.front(); q.pop();
    ans.push_back({i, j, color});

    c[i][j] = -1;
    c[i+1][j] = -1;
    c[i][j+1] = -1;
    c[i+1][j+1] = -1;

    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        int ni = i + dx;
        int nj = j + dy;
        if (valid(ni, nj) && !vis[ni][nj]) {
          int nc = canStamp(ni, nj);
          if (nc != -1) {
            vis[ni][nj] = true;
            q.push({ni, nj, nc});
          }
        }
      }
    }
  }

  bool poss = true;
  F0R(i, n) {
    F0R(j, m) {
      if (c[i][j] != -1) {
        poss = false;
      }
    }
  }
  if (poss) {
    reverse(all(ans));

    vector<vector<int>> b(n, vector<int>(m));
    cout << sz(ans) << '\n';
    for (auto [i, j, color]: ans) {
      cout << i+1 << ' ' << j+1 << ' ' << color << '\n';

      b[i][j] = color;
      b[i+1][j] = color;
      b[i][j+1] = color;
      b[i+1][j+1] = color;
    }

    /*
    F0R(i, n) {
      F0R(j, m) {
        cout << b[i][j] << ' ';
      }
      cout << '\n';
    }
    */
  }
  else {
    cout << -1 << '\n';
  }
}

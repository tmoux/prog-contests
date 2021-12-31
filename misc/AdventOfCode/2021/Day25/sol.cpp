#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
// }}}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n = 137, m = 139;
  vector<vector<char>> grid(n, vector<char>(m));
  F0R(i, n) {
    string s; cin >> s;
    F0R(j, m) {
      grid[i][j] = s[j];
    }
  }
  for (int t = 1; ; t++) {
    auto orig = grid;
    vector<vector<char>> ngrid = grid;
    // move east 
    F0R(i, n) {
      F0R(j, m) {
        if (grid[i][j] == '>') {
          int nj = (j + 1) % m;
          if (grid[i][nj] == '.') {
            ngrid[i][j] = '.';
            ngrid[i][nj] = '>';
          }
        }
      }
    }

    grid = ngrid;

    // move south
    F0R(i, n) {
      F0R(j, m) {
        if (grid[i][j] == 'v') {
          int ni = (i + 1) % n;
          if (grid[ni][j] == '.') {
            ngrid[i][j] = '.';
            ngrid[ni][j] = 'v';
          }
        }
      }
    }

    cout << "on step " << t << endl;
    F0R(i, n) {
      F0R(j, m) {
        cout << ngrid[i][j];
      }
      cout << '\n';
    }

    if (ngrid == orig) {
      cout << "stops after " << t << " steps\n";
      break;
    }
    else {
      grid = ngrid;
    }
  }
}

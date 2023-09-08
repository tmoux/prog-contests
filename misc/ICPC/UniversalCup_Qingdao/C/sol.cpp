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

bool solve() {
  int N; cin >> N;
  int r = 0;
  int i = 1;
  map<string, int> MP = {
    {"add", 0},
    {"beq", 1},
    {"bne", 2},
    {"blt", 3},
    {"bgt", 4},
  };

  vector<array<int, 3>> ins(N+1);
  for (int i = 1; i <= N; i++) {
    string s; cin >> s;
    int ty = MP[s];
    if (ty == 0) {
      int v; cin >> v;
      ins[i] = {ty, v, 0};
    }
    else {
      int v, k; cin >> v >> k;
      ins[i] = {ty, v, k};
    }
  }

  vector<vector<int>> vis(N+1, vector<int>(256, 0));
  while (i <= N) {
    if (vis[i][r]) {
      return false;
    }
    else {
      vis[i][r] = 1;
      auto [ty, v, k] = ins[i];
      if (ty == 0) {
        r = (r + v) % 256;
        i++;
      }
      else if (ty == 1) {
        if (r == v) {
          i = k;
        }
        else i++;
      }
      else if (ty == 2) {
        if (r != v) {
          i = k;
        }
        else i++;
      }
      else if (ty == 3) {
        if (r < v) {
          i = k;
        }
        else i++;
      }
      else if (ty == 4) {
        if (r > v) {
           i = k;
        }
        else i++;
      }
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << (solve() ? "Yes" : "No") << '\n';
}

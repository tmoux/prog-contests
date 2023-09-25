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

vector<int> inverse(vector<int> v) {
  vector<int> r(v);
  F0R(i, sz(v)) r[v[i]] = i;
  return r;
}

vector<vector<int>> opI(vector<vector<int>> g) {
  int N = sz(g);
  F0R(i, N) g[i] = inverse(g[i]);
  return g;
}

vector<vector<int>> opC(vector<vector<int>> g) {
  int N = sz(g);
  vector<vector<int>> r(N, vector<int>(N));
  F0R(i, N) F0R(j, N) r[j][i] = g[i][j];
  F0R(i, N) r[i] = inverse(r[i]);
  F0R(i, N) F0R(j, N) g[j][i] = r[i][j];
  return g;
}

void solve() {
  int N; cin >> N;
  int M; cin >> M;
  vector<vector<int>> A(N, vector<int>(N));
  F0R(i, N) {
    F0R(j, N) {
      cin >> A[i][j]; --A[i][j];
    }
  }
  vector<int> p(3); iota(all(p), 0);
  vector<int> d(3, 0);
  string s; cin >> s;
  for (char c: s) {
    switch (c) {
      case 'R': {
        d[p[1]] = (d[p[1]] + 1) % N;
        break;
      }
      case 'L': {
        d[p[1]] = (d[p[1]] - 1 + N) % N;
        break;
      }
      case 'D': {
        d[p[0]] = (d[p[0]] + 1) % N;
        break;
      }
      case 'U': {
        d[p[0]] = (d[p[0]] - 1 + N) % N;
        break;
      }
      case 'I': {
        swap(p[1], p[2]);
        break;
      }
      case 'C': {
        swap(p[0], p[2]);
        break;
      }
    }
  }

  vector<vector<int>> ans(N, vector<int>(N));
  F0R(i, N) {
    F0R(j, N) {
      array<int, 3> v = {i, j, A[i][j]};
      F0R(k, 3) v[k] = (v[k] + d[k]) % N;
      int a = v[p[0]];
      int b = v[p[1]];
      int c = v[p[2]];
      ans[a][b] = c;
    }
  }
  F0R(i, N) {
    F0R(j, N) {
      cout << ans[i][j]+1 << " \n"[j == N-1];
    }
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

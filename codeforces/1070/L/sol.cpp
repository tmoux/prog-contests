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

const int INF = 2;
// n = # of equations, m = # of variables
template<int N>
int gauss(vector<bitset<N>> a, int n, int m, bitset<N>& ans) {
  vector<int> where (m, -1);
  for (int col=0, row=0; col<m && row<n; ++col) {
    for (int i=row; i<n; ++i)
      if (a[i][col]) {
        swap (a[i], a[row]);
        break;
      }
    if (!a[row][col])
      continue;
    where[col] = row;

    for (int i=0; i<n; ++i)
      if (i != row && a[i][col])
        a[i] ^= a[row];
    ++row;
  }

  ans.reset();
  for (int i=0; i<m; ++i)
    if (where[i] != -1) {
      ans[i] = a[where[i]][m];
    }
  for (int i=0; i<n; ++i) {
    int sum = 0;
    for (int j=0; j<m; ++j)
      sum ^= ans[j] * a[i][j];
    if (sum - a[i][m])
      return 0;
  }

  for (int i=0; i<m; ++i)
    if (where[i] == -1)
      return INF;
  return 1;
}

void solve() {
  int N, M; cin >> N >> M;
  vector<vector<int>> adj(N);
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  bool all_even = true;
  F0R(i, N) {
    if (sz(adj[i]) % 2 != 0) all_even = false;
  }
  if (all_even) {
    cout << 1 << '\n';
    F0R(i, N) cout << 1 << " \n"[i == N-1];
  }
  else {
    const int MX = 2005;
    vector<bitset<MX>> A;
    F0R(i, N) {
      bitset<MX> v;
      if (sz(adj[i]) % 2 == 0) {
        for (int j: adj[i]) {
          v[j] = 1;
        }
      }
      else {
        v[i] = 1;
        for (int j: adj[i]) {
          v[j] = 1;
        }
        v[N] = 1;
      }
      A.push_back(v);
    }

    bitset<MX> ans;
    assert(gauss<MX>(A, N, N, ans));
    cout << 2 << '\n';
    F0R(i, N) {
      cout << ans[i]+1 << " \n"[i == N-1];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

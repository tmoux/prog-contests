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

const int maxn = 305;
int N, M, T;
int tp, tu, td;
int A[maxn][maxn];
pair<int, array<int, 4>> ans = {2e9, {}};

int pR[maxn][maxn], sR[maxn][maxn];
int pC[maxn][maxn], sC[maxn][maxn];

int eval(int x, int y) {
  if (x == y) return tp;
  else if (x < y) return tu;
  else return td;
}

pair<int, int> closest(int x, const set<pair<int, int>>& s) {
  auto it = s.lower_bound({T - x, 0});
  pair<int, int> ret = {1e9, -1};
  if (it != s.end()) {
    ckmin(ret, {it->first - (T-x), it->second});
  }
  if (it != s.begin()) {
    ckmin(ret, {(T-x) - prev(it)->first, prev(it)->second});
  }
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> T;
  cin >> tp >> tu >> td;
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j];
    }
  }
  F0R(i, N) {
    FOR(j, 1, M) {
      pR[i][j] = eval(A[i][j-1], A[i][j]) + pR[i][j-1];
    }
    FORd(j, 0, M-1) {
      sR[i][j] = eval(A[i][j+1], A[i][j]) + sR[i][j+1];
    }
  }
  F0R(j, M) {
    FOR(i, 1, N) {
      pC[i][j] = eval(A[i-1][j], A[i][j]) + pC[i-1][j];
    }
    FORd(i, 0, N-1) {
      sC[i][j] = eval(A[i+1][j], A[i][j]) + sC[i+1][j];
    }
  }

  for (int c = 0; c < N; c++) {
    for (int d = c+2; d < N; d++) {
      set<pair<int, int>> S;
      for (int j = 0; j < M; j++) {
        if (!S.empty()) {
          int x = (pR[c][j] - pC[c][j]) +
                  (-sR[d][j] + pC[d][j]);
          auto [dist, pj] = closest(x, S);
          ckmin(ans, {dist, {c, pj, d, j}});
        }
        if (j > 0) {
          int a = c, b = d;
          int x = (-pR[a][j-1] + sC[a][j-1]) +
                  (-sC[b][j-1] + sR[b][j-1]);
          S.insert({x, j-1});
        }
      }
    }
  }

  auto [a, b, c, d] = ans.second;
  cout << a+1 << ' ' << b+1 << ' ' << c+1 << ' ' << d+1 << '\n';
}

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

const int maxn = 105;
int N, M;

char G[maxn][maxn];

char mex(vector<char> v) {
  sort(all(v)); v.erase(unique(all(v)), v.end());
  F0R(i, sz(v)) {
    if (v[i]-'A' != i) return 'A' + i;
  }
  return 'A' + sz(v);
}

char compute(int i, int j) {
  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};
  vector<char> v;
  F0R(k, 4) {
    int ni = i + dx[k];
    int nj = j + dy[k];
    if (0 <= ni && ni < N && 0 <= nj && nj < M) {
      v.push_back(G[ni][nj]);
    }
  }
  return mex(v);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) F0R(j, M) G[i][j] = 'Z';
  F0R(i, N) {
    F0R(j, M) {
      if (G[i][j] != 'Z') continue;
      char c = compute(i, j);
      if (j > 0 && G[i][j-1] < c && (i == 0 || G[i][j-1] != G[i-1][j])) {
        int len = 1;
        int jj = j-1;
        while (jj >= 0 && G[i][jj] == G[i][j-1]) {
          len++;
          jj--;
        }
        if (i + len - 1 < N) {
          for (int ii = i; ii < i + len; ii++) {
            G[ii][j] = G[i][j-1];
          }
          for (int jj = j-len+1; jj <= j; jj++) {
            G[i+len-1][jj] = G[i][j-1];
          }
        }
      }
      ckmin(G[i][j], compute(i, j));
    }
  }

  F0R(i, N) {
    F0R(j, M) {
      cout << G[i][j];
    }
    cout << '\n';
  }
}

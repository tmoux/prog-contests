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

void solve() {
  int N, M; cin >> N >> M;
  if (N == 1 || M == 1) {
    cout << -1 << '\n';
    return;
  }
  bool flip = false;
  if (M % 2 == 0) {
    swap(N, M);
    flip = true;
  }
  vector<vector<int>> G(N, vector<int>(M));
  if (N % 2 == 0) {
    int C = 1;
    for (int j = 0; j < M; j++) G[0][j] = C++;
    for (int i = 1; i < N; i++) G[i][M-1] = C++;
    for (int j = M-2; j >= 0; j--) G[N-1][j] = C++;
    for (int i = N-2; i >= 1; i--) {
      if (i % 2 == 1) {
        for (int j = M-2; j >= 0; j--) G[i][j] = C++;
      }
      else {
        for (int j = 0; j < M-1; j++) G[i][j] = C++;
      }
    }
  }
  else {
    int C = 1;
    F0R(i, N) {
      if (i % 2 == 0) {
        F0R(j, M) {
          G[i][j] = C++;
          if (C == 2) C++;
        }
      }
      else {
        F0Rd(j, M) {
          G[i][j] = C++;
          if (C == 2) C++;
        }
      }
      G[N-1][M-1] = 2;
    }
    // int C = 1;
    // for (int j = 0; j < M; j++) {
    //   G[0][j] = C++;
    //   if (C == 2) C++;
    // }
    // for (int i = 1; i < N; i++) G[i][M-1] = C++;
    // for (int j = M-2; j >= 0; j--) G[N-1][j] = C++;
    // for (int i = N-2; i >= 2; i--) {
    //   if (i % 2 == 0) {
    //     for (int j = M-2; j >= 0; j--) G[i][j] = C++;
    //   }
    //   else {
    //     for (int j = 0; j < M-1; j++) G[i][j] = C++;
    //   }
    // }
    // for (int j = M-2; j >= 0; j--) {
    //   if (j == M-2) G[1][j] = 2;
    //   else G[1][j] = C++;
    // }
  }
  if (!flip) {
    F0R(i, N) {
      F0R(j, M) {
        cout << G[i][j] << " \n"[j == M-1];
      }
    }
  }
  else {
    F0R(j, M) {
      F0R(i, N) {
        cout << G[i][j] << " \n"[i == N-1];
      }
    }
  }
  fflush(stdout);
  int dx[] = {0, 1, -1, 0};
  int dy[] = {1, 0, 0, -1};
  F0R(i, N) {
    F0R(j, M) {
      int cnt = 0;
      assert(1 <= G[i][j] && G[i][j] <= N*M);
      F0R(k, 4) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (0 <= ni && ni < N && 0 <= nj && nj < M) {
          if (gcd(G[i][j], G[ni][nj]) == 1) {
            cnt++;
          }
        }
      }
      if (cnt < 2) {
        cout << "FAILED " << i << ' ' << j << ' ' << G[i][j] << endl;
      }
      assert(cnt >= 2);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

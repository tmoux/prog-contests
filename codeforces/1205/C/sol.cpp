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

/*
** Length 3 queries can determine all odd positions.
** Similarly we can determine all even positions, up to parity.
** So now we have two options.
** We can precompute what the answers would be for any query.
** Now we just have to find one query that distinguishes between them.
** Conjecture: one such query always exists (probably since the corners have different values).
 */

#define V vector

int ask(int x1, int y1, int x2, int y2) {
  cout << "? " << x1+1 << ' ' << y1+1 << ' ' << x2+1 << ' ' << y2+1 << endl;
  int r; cin >> r;
  return r;
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N;
  cin >> N;

  auto computeDP = [&](V<V<int>> g) -> V<V<V<V<int>>>> {
    V<V<V<V<int>>>> dp(N, V<V<V<int>>>(N, V<V<int>>(N, V<int>(N))));
    auto check = [&](int x1, int y1, int x2, int y2) -> int {
      if (x1 > x2) return 0;
      if (y1 > y2) return 0;
      if (!(0 <= x1 && x1 < N)) return 0;
      if (!(0 <= y1 && y1 < N)) return 0;
      if (!(0 <= x2 && x2 < N)) return 0;
      if (!(0 <= y2 && y2 < N)) return 0;
      return g[x1][y1] == g[x2][y2];
    };
    for (int i1 = N-1; i1 >= 0; i1--) {
      for (int j1 = N-1; j1 >= 0; j1--) {
        for (int i2 = i1; i2 < N; i2++) {
          for (int j2 = j1; j2 < N; j2++) {
            if (i1 == i2 && j1 == j2) dp[i1][j1][i2][j2] = 1;
            else if (g[i1][j1] != g[i2][j2]) dp[i1][j1][i2][j2] = 0;
            else if ((i2-i1) + (j2-j1) == 1) dp[i1][j1][i2][j2] = g[i1][j1] == g[i2][j2];
            else {
              dp[i1][j1][i2][j2] |= check(i1+1, j1, i2-1, j2) && dp[i1+1][j1][i2-1][j2];
              dp[i1][j1][i2][j2] |= check(i1+1, j1, i2, j2-1) && dp[i1+1][j1][i2][j2-1];
              dp[i1][j1][i2][j2] |= check(i1, j1+1, i2-1, j2) && dp[i1][j1+1][i2-1][j2];
              dp[i1][j1][i2][j2] |= check(i1, j1+1, i2, j2-1) && dp[i1][j1+1][i2][j2-1];
            }
          }
        }
      }
    }
    return dp;
  };

  vector<vector<int>> G(N, vector<int>(N));
  G[0][0] = 1;

  auto update = [&](int x1, int y1, int x2, int y2) -> void {
    G[x2][y2] = 1 ^ ask(x1, y1, x2, y2) ^ G[x1][y1];
  };
  for (int i = 0; i < N; i++) {
    for (int j = i&1; j < N; j += 2) {
      if (i == 0 && j == 0) continue;
      if (i == N-1 && j == N-1) continue;
      if (j-2 >= 0) update(i, j-2, i, j);
      else if (i-2 >= 0) update(i-2, j, i, j);
      else update(i-1, j-1, i, j);
    }
  }

  // assume G[0][1] = 0
  for (int i = 0; i < N; i++) {
    if (i == 0) {
      for (int j = 3; j < N; j += 2) {
        update(i, j-2, i, j);
      }
    }
    else {
      for (int j = i % 2 == 0 ? N-2 : N-1; j >= 0; j -= 2) {
        if (j-1 >= 0) update(i-1, j-1, i, j);
        else G[i][j] = 1 ^ ask(i, j, i, j+2) ^ G[i][j+2];
      }
    }
  }

  vector<vector<int>> G2 = G;
  for (int i = 0; i < N; i++) {
    for (int j = (i&1)^1; j < N; j += 2) {
      G2[i][j] ^= 1;
    }
  }


  auto dp1 = computeDP(G);
  auto dp2 = computeDP(G2);

  F0R(i1, N) {
    F0R(j1, N) {
      FOR(i2, i1, N) {
        FOR(j2, j1, N) {
          if ((i2 - i1) + (j2 - j1) <= 1) continue;
          if (dp1[i1][j1][i2][j2] != dp2[i1][j1][i2][j2]) {
            int x = ask(i1, j1, i2, j2);
            auto ans = x == dp1[i1][j1][i2][j2] ? G : G2;
            cout << "!" << endl;
            F0R(i, N) {
              F0R(j, N) {
                cout << ans[i][j];
              }
              cout << endl;
            }
            return 0;
          }
        }
      }
    }
  }
  assert(false);
}

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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  array<array<int, 4>, 4> C;
  F0R(i, 4) F0R(j, 4) C[i][j] = 0;
  F0R(i, N) {
    int x, y; cin >> x >> y;
    x %= 4, y %= 4;
    C[x][y]++;
  }
  vector<pair<int, int>> v;
  F0R(i, 4) {
    F0R(j, 4) {
      if (C[i][j] > 0) {
        v.push_back({i, j});
      }
    }
  }

  auto getb = [&](pair<int, int> a, pair<int, int> b) -> int {
    return std::gcd(abs(a.first - b.first), abs(a.second - b.second));
  };

  auto geta = [&](int x1, int y1, int x2, int y2, int x3, int y3) -> int {
    return abs((x1 * y2 + x2 * y3 + x3 * y1) - (y1 * x2 + y2 * x3 + y3 * x1)) % 4;
  };

  ll ans = 0;
  F0R(a, sz(v)) {
    FOR(b, a, sz(v)) {
      FOR(c, b, sz(v)) {
        int x = (getb(v[a], v[b]) + getb(v[b], v[c]) + getb(v[c], v[a])) % 4;
        int y = geta(v[a].first, v[a].second,
                     v[b].first, v[b].second,
                     v[c].first, v[c].second);
        if (x == y) {
          ll ways;
          if (a == b && b == c) {
            int d = C[v[a].first][v[a].second];
            ways = 1LL * d * (d - 1) * (d - 2) / 6;
          }
          else if (a == b) {
            int d = C[v[a].first][v[a].second];
            int e = C[v[c].first][v[c].second];
            ways = 1LL * d * (d - 1) / 2 * e;
          }
          else if (b == c) {
            int d = C[v[b].first][v[b].second];
            int e = C[v[a].first][v[a].second];
            ways = 1LL * d * (d - 1) / 2 * e;
          }
          else if (a == c) {
            int d = C[v[a].first][v[a].second];
            int e = C[v[b].first][v[b].second];
            ways = 1LL * d * (d - 1) / 2 * e;
          }
          else {
            ways = 1LL * C[v[a].first][v[a].second] *
              C[v[b].first][v[b].second] *
              C[v[c].first][v[c].second];
          }
          ans += ways;
        }
      }
    }
  }
  cout << ans << '\n';
}

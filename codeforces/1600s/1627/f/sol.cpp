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

int solve() {
  int n, k; cin >> n >> k;
  vector<vector<int>> up(k+1, vector<int>(k+1, 0));
  vector<vector<int>> down(k+1, vector<int>(k+1, 0));
  vector<vector<int>> left(k+1, vector<int>(k+1, 0));
  vector<vector<int>> right(k+1, vector<int>(k+1, 0));
  auto flip = [&](int x) {
    return k-1-x;
  };
  auto add_edges = [&](int r1, int c1, int r2, int c2) {
    if (r1 == r2) {
      if (c1 > c2) swap(c1, c2);
      down[r2][c2]++;
      up[r2+1][c2]++;
    }
    else if (c1 == c2) {
      if (r1 > r2) swap(r1, r2);
      right[r2][c2]++;
      left[r2][c2+1]++;
    }
    else assert(false);
  };
  F0R(i, n) {
    int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
    r1--; c1--; r2--; c2--;
    add_edges(r1, c1, r2, c2);
    add_edges(flip(r1), flip(c1), flip(r2), flip(c2));
  }

  const int INF = 1e9;
  vector<vector<int>> dist(k+1, vector<int>(k+1, INF));
  auto dijkstra = [&]() {
    priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>> pq;
    pq.push({0,0,0});
    dist[0][0] = 0;

    while (!pq.empty()) {
      auto [d, i, j] = pq.top(); pq.pop();
      if (d > dist[i][j]) continue;

      if (i > 0) {
        if (ckmin(dist[i-1][j], dist[i][j] + up[i][j])) {
          pq.push({dist[i-1][j], i-1, j});
        }
      }
      if (i < k) {
        if (ckmin(dist[i+1][j], dist[i][j] + down[i][j])) {
          pq.push({dist[i+1][j], i+1, j});
        }
      }
      if (j > 0) {
        if (ckmin(dist[i][j-1], dist[i][j] + left[i][j])) {
          pq.push({dist[i][j-1], i, j-1});
        }
      }
      if (j < k) {
        if (ckmin(dist[i][j+1], dist[i][j] + right[i][j])) {
          pq.push({dist[i][j+1], i, j+1});
        }
      }
    }
  };
  dijkstra();

  return n-dist[k/2][k/2];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  REP(T) {
    cout << solve() << '\n';
  }
}

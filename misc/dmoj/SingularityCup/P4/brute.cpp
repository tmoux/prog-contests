#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M, Q; cin >> N >> M >> Q;
  vector<vector<int>> A(N, vector<int>(M));
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j];
    }
  }

  vector<vector<ll>> prefix(N, vector<ll>(M));
  vector<array<int, 3>> batch;
  auto rebuild = [&]() -> void {
    for (auto& [r, c, v]: batch) {
      A[r][c] = v;
    }
    batch.clear();
    F0R(i, N) {
      F0R(j, M) {
        prefix[i][j] = A[i][j];
        if (j > 0) prefix[i][j] += prefix[i][j-1];
      }
    }
  };

  vector<vector<int>> S(N, vector<int>(M));
  auto query = [&](int r, int c, int h) -> ll {
    ll ans = 0;
    for (int i = 0; i < h; i++) {
      ans += prefix[r + i][c + i] - (c == 0 ? 0 : prefix[r + i][c - 1]);
    }

    F0Rd(idx, sz(batch)) {
      auto& [i, j, v] = batch[idx];
      if (S[i][j]) continue;
      S[i][j] = 1;

      if (r <= i && i < r + h && c <= j && j <= c + (i - r)) {
        ans -= A[i][j];
        ans += v;
      }
    }
    for (auto& [i, j, c]: batch) S[i][j] = 0;
    return ans;
  };

  int NUM_REBUILDS = 100;
  int MAX_BATCH_SIZE = Q / NUM_REBUILDS;
  rebuild();
  REP(Q) {
    int t; cin >> t;
    if (t == 1) {
      int r, c, v; cin >> r >> c >> v;
      r--, c--;
      batch.push_back({r, c, v});
      if (sz(batch) >= MAX_BATCH_SIZE) {
        rebuild();
      }
    }
    else {
      int r, c, h; cin >> r >> c >> h;
      r--, c--;
      r -= h-1;
      cout << query(r, c, h) << '\n';
    }
  }
}

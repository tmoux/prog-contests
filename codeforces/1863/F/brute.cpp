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
  int N; cin >> N;
  vector<ll> A(N);
  F0R(i, N) cin >> A[i];

  ll total = 0;
  for (auto& x: A) total ^= x;

  // BF
  vector<vector<int>> seen(N, vector<int>(N));
  vector<vector<int>> dist(N, vector<int>(N));
  queue<pair<int, int>> q; q.push({0, N-1});

  auto bs = [&](int x) {
    return bitset<4>(x);
  };

  vector<int> ans(N);
  while (!q.empty()) {
    auto [l, r] = q.front(); q.pop();
    if (l == r) {
      ans[l] = 1;
    }
    ll x = 0;
    FOR(i, l, r+1) x ^= A[i];
    ll a = 0;

    auto upd = [&](int y, int z, int l, int r) {
      // cout << l << ' ' << r << " -> " << y << ' ' << z << endl;
      if (!seen[y][z]) {
        seen[y][z] = 1;
        q.push({y, z});
        dist[y][z] = dist[l][r] + 1;
      }
    };
    FOR(i, l, r) {
      a ^= A[i];
      ll b = x ^ a;
      if (a == b) {
        upd(l, i, l, r);
        upd(i+1, r, l, r);
      }
      else if (a > b) {
        // cout << bs(x) << ' ' << bs(a) << endl;
        upd(l, i, l, r);
      }
      else {
        // cout << bs(x) << ' ' << bs(b) << endl;
        upd(i+1, r, l, r);
      }
    }
  }
  F0R(i, N) {
    cout << ans[i];
  }
  cout << '\n';
  // cout << ans << endl;
  // F0R(i, N) {
  //   if (ans[i]) {
  //     cout << dist[i][i] << ' ';
  //   }
  // }
  // cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

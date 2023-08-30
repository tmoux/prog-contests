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
  int N, K; cin >> N >> K;

  vector<int> used(2*N);
  vector<pair<int, int>> edges;
  REP(K) {
    int x, y; cin >> x >> y;
    x--, y--;
    used[x] = used[y] = 1;
    edges.emplace_back(x, y);
  }

  vector<int> v;
  F0R(i, 2*N) {
    if (!used[i]) v.push_back(i);
  }
  for (int i = 0; i < sz(v)/2; i++) {
    edges.emplace_back(v[i], v[i+sz(v)/2]);
  }

  auto isec = [&](pair<int, int> A, pair<int, int> B) -> bool {
    auto [a, b] = A;
    auto [c, d] = B;
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return a < c && c < b && b < d;
  };

  int ans = 0;
  F0R(i, sz(edges)) {
    FOR(j, i+1, sz(edges)) {
      if (isec(edges[i], edges[j]) || isec(edges[j], edges[i])) ans++;
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

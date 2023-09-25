#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

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
  vector<int> C(N);
  F0R(i, N) cin >> C[i];
  vector<pair<int, int>> v; // cost, index
  F0R(i, N) {
    while (!v.empty() && v.back().first >= C[i]) v.pop_back();
    v.push_back({C[i], i});
  }
  int K; cin >> K;
  int X = K / v[0].first; // number coins must use
  int num_used = 0, cur_cost = 0;
  int c1 = v[0].first;

  vector<int> ans(N+1);
  vector<int> cnt(N);
  int cur = X;
  cur_cost = X * c1;
  cnt[v[0].second] = cur;
  for (int i = 0; i + 1 < sz(v); i++) {
    int delta = v[i+1].first - v[i].first;
    // int take = (K - cur_cost) / delta;
    int take = min(cur, (K - cur_cost) / delta);
    // cout << i << ": " << take << endl;

    cnt[v[i].second] -= take;
    cnt[v[i+1].second] += take;
    cur_cost += delta * take;
    cur = take;
  }
  // for (int i = sz(v)-1; i >= 0; i--) {
  //   int ci = v[i].first;
  //   int take;
  //   if (i == 0) {
  //     take = X - num_used;
  //   }
  //   else take = (K - cur_cost - c1 * (X - num_used)) / (ci - c1);

  //   ans[0] += take;
  //   ans[v[i].second+1] -= take;
  //   num_used += take;
  //   cur_cost += take * ci;

  //   assert(cur_cost + (X - num_used) * c1 <= K);
  // }

  F0R(i, N) {
    ans[0] += cnt[i];
    ans[i+1] -= cnt[i];
  }
  for (int i = 1; i < N; i++) {
    ans[i] += ans[i-1];
  }
  F0R(i, N) {
    cout << ans[i] << " \n"[i == N-1];
  }
  assert(ans[0] == X);
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

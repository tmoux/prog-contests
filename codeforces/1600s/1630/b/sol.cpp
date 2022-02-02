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
  int n, k; cin >> n >> k;
  vector<int> a(n), cnt(n+1);
  F0R(i, n) {
    cin >> a[i];
    cnt[a[i]]++;
  }
  for (int i = 1; i <= n; i++) cnt[i] += cnt[i-1];
  int target = (k+n+1)/2;

  pair<int, array<int,2>> best = {n+5, {-1,-1}};
  for (int x = 1, y = 1; x <= n; x++) {
    while (y <= n && cnt[y] - cnt[x-1] < target) y++;
    if (y <= n && cnt[y] - cnt[x-1] >= target) {
      ckmin(best, {y-x, {x,y}});
    }
  }

  assert(best.second[0] != -1);
  auto [x, y] = best.second;
  vector<int> ans;
  vector<int> pre(n);
  for (int i = 0; i < n; i++) {
    pre[i] = (x <= a[i] && a[i] <= y) ? 1 : -1;
    if (i > 0) pre[i] += pre[i-1];
  }
  int cur = 1;
  for (int i = 0; i < n; i++) {
    if (cur == k) break;
    if (pre[i] == cur) {
      ans.push_back(i);
      cur++;
    }
  }
  ans.push_back(n-1);

  cout << x << ' ' << y << '\n';
  assert(sz(ans) == k);
  for (int i = 0; i < sz(ans); i++) {
    cout << (i == 0 ? 0 : ans[i-1]+1)+1 << ' ' << ans[i]+1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;

template <class K, class V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<K, V, std::less<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
/* order_of_key(k), how many elements <k */
/* find_by_order(k), k'th element (from 0) */
/* both logn */

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
  int n; cin >> n;
  vector<int> a(n); for (auto& i: a) cin >> i;

  auto check_avg = [&](double x) {
    vector<double> v(n);
    F0R(i, n) v[i] = a[i] - x;
    vector<double> dp(n);
    F0Rd(i, n) {
      dp[i] = v[i] + (i+2 >= n ? 0 : dp[i+2]);
      ckmax(dp[i], v[i] + (i+1 >= n ? 0 : dp[i+1]));
    }
    return max(dp[0], dp[1]) >= 0;
  };

  auto check_med = [&](int x) {
    vector<int> v(n);
    F0R(i, n) v[i] = a[i] < x ? -1 : 1;
    vector<int> dp(n);
    F0Rd(i, n) {
      dp[i] = v[i] + (i+2 >= n ? 0 : dp[i+2]);
      ckmax(dp[i], v[i] + (i+1 >= n ? 0 : dp[i+1]));
    }
    return max(dp[0], dp[1]) > 0;
  };

  {
    double lo = 0, hi = 1e9+9;
    REP(300) {
      double mid = (lo+hi)/2;
      (check_avg(mid) ? lo : hi) = mid;
    }
    cout << fixed << setprecision(10) << lo << '\n';
  }
  {
    int lo = 0, hi = 1e9+9;
    while (lo + 1 < hi) {
      int mid = (lo+hi)/2;
      (check_med(mid) ? lo : hi) = mid;
    }
    cout << lo << '\n';
  }
}

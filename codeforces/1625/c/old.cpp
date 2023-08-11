#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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
  int n, l, k; cin >> n >> l >> k;
  vector<int> d(n); 
  F0R(i, n) {
    cin >> d[i];
  }
  
  vector<int> dist(n);
  for (int i = 0; i < n-1; i++) {
    dist[i] = d[i+1] - d[i];
  }
  dist[n-1] = l - d[n-1];

  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  vector<bool> taken(n, false);
  vector<int> b(n);
  int have = 0;
  int curSpeed = a[0];
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] <= curSpeed) {
      curSpeed = a[i];
      have++;
      taken[i] = true;
    }
    b[i] = curSpeed;

    ans += 1LL * curSpeed * dist[i];
  }

  while (have < n-k) {

    ll minAdd = 1e18;
    int idx = -1;
    for (int i = 0; i < n; i++) {
      if (taken[i]) continue;
      int j = i;
      while (j < n && !taken[j]) j++;
      int speed = b[i];
      int r = j == n ? l : d[j];
      ll cost = 1LL * (r-d[i]) * (a[i] - speed);
      if (cost < minAdd) {
        minAdd = cost;
        idx = i;
      }
    }

    assert(idx != -1);
    taken[idx] = true;
    ans += minAdd;
    for (int j = idx; j < n && !taken[j]; j++) {
      b[j] = a[idx];
    }
    have++;
  }

  cout << ans << '\n';
}

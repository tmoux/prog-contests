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

bool check(vector<int> d) {
  ll sum = std::accumulate(all(d), 0LL);
  if (sum&1) return 0;
  sort(all(d), greater());
  int n = sz(d);
  vector<ll> sfx(n+1);
  for (int i = n-1; i >= 0; i--) sfx[i] = d[i] + sfx[i+1];
  ll lhs = 0;
  for (int k = 1; k <= n; k++) {
    lhs += d[k-1];
    ll rhs = 1LL * k * (k-1);
    int lo = k-1, hi = n;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      if (d[mid] > k) lo = mid;
      else hi = mid;
    }
    rhs += 1LL * (lo - k + 1) * k;
    rhs += sfx[lo+1];
    if (lhs > rhs) {
      return false;
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<int> d(N);
  F0R(i, N) cin >> d[i];

  ll sumDegree = std::accumulate(all(d), 0LL);
  bool isOdd = sumDegree & 1;
  // find least
  int lo = 0, hi = N;
  int least = -1;
  for (int k = 0; k <= N; k++) {
    vector<int> nd = d; nd.push_back(k);
    cout << k << ": " << check(nd) << endl;
  }
}

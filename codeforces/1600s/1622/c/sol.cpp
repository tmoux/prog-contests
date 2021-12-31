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

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
// }}}

ll ceil(ll a, ll b) {
  return (a+b-1)/b;
}

ll solve() {
  int n; cin >> n;
  ll k; cin >> k;
  vector<ll> a(n);
  ll sum = 0;
  for (auto& i: a) {
    cin >> i;
    sum += i;
  }
  ll target = sum - k;
  if (target <= 0) return 0LL;
  sort(all(a));
  vector<ll> triSum(n+1, 0LL);
  for (int i = n-1; i >= 0; i--) {
    triSum[i] = a[i] - a[0] + triSum[i+1];
  }

  /*
  ll ans = target;
  for (int i = 0; i <= n-1; i++) {
    ll x = ceil(target - triSum[n-i], i+1);
    ckmin(ans, x+i);
  }
  return ans;
  */
  auto check = [&](ll steps) -> bool {
    ll best = steps;
    for (ll i = 0; i <= min((ll)n-1, steps); i++) {
      //i sets
      ll x = steps - i;
      ll tr = x + triSum[n-i] + i*x;

      ckmax(best, tr);
    }
    //cout << steps << ": " << best << endl;
    return best >= target;
  };

  ll lo = 0, hi = target + 1;
  while (lo + 1 < hi) {
    ll mid = (lo+hi)/2;
    (check(mid) ? hi : lo) = mid;
  }
  return hi;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    cout << solve() << '\n';
  }
}

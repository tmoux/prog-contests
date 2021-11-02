#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) requires Container<U<T>>
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}


int solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (auto& i: a) cin >> i;
  reverse(all(a));
  vector<ll> pfx(n);
  for (int i = 0; i < n; i++) {
    pfx[i] = a[i];
    if (i > 0) pfx[i] += pfx[i-1];
  }
  const int maxk = 450;
  const ll INF = 1e18;

  //dp[i][k] is the minimum sum of a segment of length k ending and i
  vector<vector<ll>> dp(n, vector<ll>(maxk, 0));
  for (int i = 0; i < n; i++) {
    dp[i][1] = a[i];
    for (int k = 2; k <= min(i, maxk); k++) {
      ll sum = pfx[i] - pfx[i-k];
      if (dp[i-k][k-1] > sum) {
        dp[i][k] = sum;
      }
    }

    if (i > 0) {
      F0R(k, maxk) ckmax(dp[i][k], dp[i-1][k]);
    }

    //cout << i << endl;
    /*
    cout << i << ": ";
    for (int k = 1; k <= 3; k++) {
      cout << dp[i][k] << ' ';
    }
    cout << '\n';
    */
  }

  int ans = 0;
  F0R(k, maxk) if (dp[n-1][k] > 0) ckmax(ans, k);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    cout << solve() << '\n';
  }
}

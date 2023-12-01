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

/*
** Subtask 2:
** Process all queries at once, in decreasing order of bits
** Maintain a set of nodes (queries/current # ops, cost, num 0's)
** Process each level in 60 * N, 60^2 * Q in total
** Might be too slow?
** Don't know how to handle updates to cost/num 0's
**
** It seems that most times, answer goes up by 1 every N?
 */

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  vector<ll> A(N);
  F0R(i, N) cin >> A[i];

  const int MX = 60;
  auto query = [&](ll k) {
    vector<ll> B = A;
    for (int i = MX; i >= 0; i--) {
      ll cost = 0;
      for (auto x: B) {
        if (x & (1LL << i)) continue;
        else {
          ll y = ((x >> i) | 1) << i;
          cost += y - x;

          // Check for overflow
          if (cost > k) break;
        }
      }
      if (cost <= k) {
        k -= cost;
        for (auto& x: B) {
          if (x & (1LL << i)) continue;
          else {
            ll y = ((x >> i) | 1) << i;
            x = y;
          }
        }
      }
    }

    ll ans = B[0];
    for (auto x: B) ans &= x;
    return ans;
  };

  for (int i = 1; i <= 100; i++) {
    cout << i << ": " << query(i) << endl;
  }

  // REP(Q) {
  //   ll k; cin >> k;
  //   cout << query(k) << '\n';
  // }
}

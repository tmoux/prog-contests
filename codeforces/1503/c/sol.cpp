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

/*
  First subtract of \sum c_i from answer.
  We want to compute the minimum "excess" required.
  Claim: the answer (A) is equal to the min excess required to go from
  min a_i to max a_i (B)
  Proof: clearly A <= B, since we can turn any construction for B into a construction for A.
  Also, B <= A, since for any cycle, we can just take the excess from that part of the cycle.
  Thus this admits a greedy solution.
  We start at min a_i, and our goal is to get up to max a_i with as little cost as possible.

 */

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<pair<int, int>> A;
  ll ans = 0;
  F0R(i, N) {
    int a, c; cin >> a >> c;
    A.emplace_back(a, c);
    ans += c;
  }
  sort(all(A));
  int cur = A.front().first, max_a = A.back().first;
  F0R(i, N) {
    if (cur >= max_a) break;
    ans += max(0, A[i].first - cur);
    ckmax(cur, A[i].first + A[i].second);
  }
  cout << ans << '\n';
}

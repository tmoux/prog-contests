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

// If have x nodes, need x <= S <= x*(x+1)/2
// Better to have fewer nodes to reduce branching factor
// If have x currently, S -> S - x on next level
// Let x' be min s.t. x'*(x'+1)/2 >= S - x
// the amount we take is min(x - x', B * prev)

int min_x(ll S) {
  int x = (sqrt(1 + 8 * S) - 1) / 2 + 1;
  while (x-1 >= 0 && 1LL*(x-1)*x/2 >= S) x--;
  return x;
}

pair<bool, vector<int>> check(int N, ll S, int B) {
  vector<int> v = {1};
  while (N > 0) {
    if (!(N <= S && S <= 1LL*N*(N+1)/2)) return {false, v};
    int x = min_x(S - N);
    ll take = min((ll)N - x, 1LL * v.back() * B);
    v.push_back(take);
    S -= N;
    N -= take;
  }
  return {true, v};
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  ll S; cin >> S;

  S -= N;
  N--;

  if (!(N <= S && S <= 1LL*N*(N+1)/2)) {
    cout << "No\n";
    return 0;
  }

  int lo = 0, hi = N+1;
  vector<int> ans;
  while (lo + 1 < hi) {
    int mid = std::midpoint(lo, hi);
    auto [poss, v] = check(N, S, mid);
    if (poss) {
      hi = mid;
      ans = v;
    }
    else lo = mid;
  }

  vector<int> deg(N+1);
  vector<int> cur = {1};
  int B = hi;
  int c = 2;
  cout << "Yes\n";
  for (int i = 1; i < sz(ans); i++) {
    int idx = 0;
    vector<int> ncur;
    REP(ans[i]) {
      if (deg[cur[idx]] == B) idx++;
      assert(idx < sz(cur));
      cout << cur[idx] << ' ';
      deg[cur[idx]]++;
      ncur.push_back(c++);
    }
    cur = ncur;
  }
  cout << '\n';
}

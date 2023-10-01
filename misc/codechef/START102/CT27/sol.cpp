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

ll solve() {
  int N, M; cin >> N >> M;
  vector<int> A(N); for (auto& x: A) cin >> x;
  vector<int> B(M); for (auto& x: B) cin >> x;
  if (*min_element(all(A)) > *min_element(all(B))) return -1;
  vector<int> v = A;
  sort(all(v)); v.erase(unique(all(v)), v.end());
  map<int, vector<int>> mp;
  F0R(i, N) mp[A[i]].push_back(i);
  auto find_next = [&](int i, int x) -> int {
    auto it = upper_bound(all(v), x);
    int y = *prev(it);
    auto it2 = upper_bound(all(mp[y]), i);
    if (it2 != mp[y].end()) return *it2;
    else return mp[y].front();
  };

  ll ans = 1;
  int idx = -1;
  for (auto x: B) {
    int new_idx = find_next(idx, x);
    // DEBUG(new_idx);
    assert(A[new_idx] <= x);
    ans += x - A[new_idx];
    if (new_idx <= idx) ans++;
    idx = new_idx;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}

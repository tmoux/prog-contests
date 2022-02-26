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
  int n, m; cin >> n >> m;
  map<int, int> freq;
  vector<int> a(n);
  for (auto& i: a) {
    cin >> i;
    freq[i]++;
  }

  map<int, vector<int>> nums;
  for (auto [x, cnt]: freq) {
    nums[cnt].push_back(x);
  }
  // for (auto& [_, v]: nums) sort(all(v));

  map<int, set<int>> bad;
  F0R(i, m) {
    int x, y; cin >> x >> y;
    bad[x].insert(y);
  }

  ll ans = 0;
  for (auto [x, cnt_x]: freq) {
    for (auto& [cnt_y, v]: nums) {
      int idx = sz(v)-1;
      while (idx >= 0 && bad[x].count(v[idx])) {
        idx--;
      }
      if (idx >= 0 && v[idx] > x) {
        int y = v[idx];
        ll tr = 1LL * (cnt_x + cnt_y) * (x + y);
        ckmax(ans, tr);
        // if (ckmax(ans, tr)) {
          // cout << x << ' ' << y << ": " << tr << endl;
          //cout << x << ' ' << cnt_x << ' ' < y << ' ' << cnt_y << ": " << tr << endl;
        // }
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

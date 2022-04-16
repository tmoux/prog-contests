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

int solve() {
  int n; cin >> n;
  vector<vector<int>> child(n);
  for (int i = 1; i < n; i++) {
    int p; cin >> p; p--;
    child[p].push_back(i);
  }
  vector<vector<int>> sib;
  sib.push_back({0});
  F0R(i, n) if (!child[i].empty()) sib.push_back(child[i]);
  sort(all(sib), [](auto& a, auto& b) { return sz(a) > sz(b); });

  int ans = 0;
  int cnt = 0;
  multiset<int> ms;
  int sub = 0;
  int pt = 0;
  while (cnt < n) {
    ans++;
    // spread
    while (!ms.empty() && *ms.begin() <= sub) ms.erase(ms.begin());
    sub++;
    cnt += sz(ms);
    while (!ms.empty() && *ms.begin() <= sub) ms.erase(ms.begin());

    // inject
    if (pt < sz(sib)) {
      // cout << "adding " << (sib[pt][0] + 1) << endl;
      cnt++;
      ms.insert(sz(sib[pt]) - 1 + sub);
      pt++;
    }
    else if (!ms.empty()) {
      auto it = prev(ms.end());
      int x = *it - 1;
      ms.erase(it);
      ms.insert(x);
      cnt++;
    }
    // cout << ans << ": " << cnt << endl;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}

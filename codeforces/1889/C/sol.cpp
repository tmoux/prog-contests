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

int solve() {
  int N, M, K; cin >> N >> M >> K;
  assert(K == 2);
  vector<pair<int, int>> A(M);

  vector<vector<int>> open(N+1), close(N+1);
  F0R(i, M) {
    int l, r; cin >> l >> r;
    l--, r--;
    open[l].push_back(i);
    close[r+1].push_back(i);
  }

  set<int> cur;
  vector<int> only(M);
  int uncovered = 0;
  map<pair<int, int>, int> mp;
  F0R(i, N) {
    for (auto id: open[i]) cur.insert(id);
    for (auto id: close[i]) cur.erase(id);

    if (sz(cur) == 0) uncovered++;
    else if (sz(cur) == 1) {
      int a = *cur.begin();
      only[a]++;
    }
    else if (sz(cur) == 2) {
      int a = *cur.begin();
      int b = *next(cur.begin());
      mp[{a, b}]++;
    }
  }

  int ans = 0;
  auto sortedOnly = only;
  sort(all(sortedOnly), greater());
  ckmax(ans, uncovered + sortedOnly[0] + sortedOnly[1]);

  // DEBUG(uncovered);
  for (auto [p, c]: mp) {
    auto [a, b] = p;
    ckmax(ans, uncovered + only[a] + only[b] + c);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}

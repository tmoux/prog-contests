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

const int MX = 1e6+6;
const int MK = 21;
int par[MK][MX];

int jump(int i, int k) {
  F0Rd(j, MK) {
    if (k & (1 << j)) {
      i = par[j][i];
    }
  }
  return i;
}

vector<int> queries[MX];
vector<pair<int, int>> adj[MX];
int ans[MX];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  memset(ans, -1, sizeof ans);
  int cur_idx = 0, nxt = 1;

  int Q; cin >> Q;
  stack<int> st; // points to previous node
  F0R(t, Q) {
    char c; cin >> c;
    if (c == '+') {
      int x; cin >> x;
      adj[cur_idx].emplace_back(nxt, x);
      par[0][nxt] = cur_idx;
      for (int i = 1; i < MK; i++) {
        par[i][nxt] = par[i-1][par[i-1][nxt]];
      }
      st.push(cur_idx);
      cur_idx = nxt;
      nxt++;
    }
    else if (c == '-') {
      int k; cin >> k;
      st.push(cur_idx);
      cur_idx = jump(cur_idx, k);
    }
    else if (c == '!') {
      assert(!st.empty());
      cur_idx = st.top(); st.pop();
    }
    else if (c == '?') {
      queries[cur_idx].push_back(t);
    }
    else assert(false);
  }
  vector<int> cnt(MX);
  int num_distinct = 0;
  auto dfs = y_combinator([&](auto dfs, int i) -> void {
    for (auto t: queries[i]) {
      ans[t] = num_distinct;
    }
    for (auto [j, x]: adj[i]) {
      if (++cnt[x] == 1) num_distinct++;
      dfs(j);
      if (--cnt[x] == 0) num_distinct--;
    }
  });
  dfs(0);
  F0R(t, Q) {
    if (ans[t] != -1) cout << ans[t] << '\n';
  }
}

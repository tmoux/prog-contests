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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<vector<int>> stacks(N);
  F0R(i, N) {
    int k; cin >> k;
    REP(k) {
      int x; cin >> x;
      x--;
      // Ignore self-loops, they don't matter anyways
      if (x != i) stacks[i].push_back(x);
    }
  }
  stack<int> st;
  vector<bool> onstack(N);
  vector<int> vis(N);
  auto dfs = y_combinator([&](auto dfs, int i) -> void {
    if (vis[i]) return;
    if (onstack[i]) {
      // remove cycle
      while (true) {
        int d = st.top();
        st.pop();
        stacks[d].pop_back();
        onstack[d] = 0;
        if (d == i) break;
      }
    }
    st.push(i);
    onstack[i] = 1;

    if (!stacks[i].empty()) {
      int j = stacks[i].back();
      dfs(j);
    }
  });

  F0R(i, N) {
    if (!vis[i]) {
      dfs(i);
      while (!st.empty()) {
        int j = st.top(); st.pop();
        onstack[j] = 0;
        vis[j] = 1;
      }
    }
  }

  vector<int> ans(N, -1);
  auto F = y_combinator([&](auto F, int i) -> int {
    if (ans[i] != -1) return ans[i];
    if (stacks[i].empty()) return ans[i] = i;
    return ans[i] = F(stacks[i].back());
  });

  F0R(i, N) {
    cout << F(i)+1 << ' ';
  }
  cout << '\n';
}

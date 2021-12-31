#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }
// }}}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, k; cin >> n >> k;
  vector<int> left(n), right(n);
  string s; cin >> s;
  F0R(i, n) {
    int l, r; cin >> l >> r;
    l--; r--;
    left[i] = l;
    right[i] = r;
  }

  // Inorder DFS to find timings and 
  // next unique char in inorder traversal
  string S(n+1, 'a');
  vector<int> tin(n);
  vector<char> nextUnique(n+1, 'a'); //next unique char 
  {
    int t = 0;
    y_combinator([&](auto dfs, int i, int p, int& t) -> void {
      if (left[i] != -1) {
        dfs(left[i], i, t);
      }
      tin[i] = t++;
      S[tin[i]] = s[i];
      if (right[i] != -1) {
        dfs(right[i], i, t);
      }
    })(0, -1, t);
    for (int i = n-1; i >= 0; i--) {
      nextUnique[i] = S[i] == S[i+1] ? nextUnique[i+1] : S[i+1];
    }
  }

  vector<bool> marked(n, false);
  vector<int> befores, afters;
  auto dfs = y_combinator([&](auto dfs, int i) -> void {
    int t = tin[i];
    if (left[i] != -1) {
      if (!marked[t]) afters.push_back(t);
      dfs(left[i]);
      if (!afters.empty() && afters.back() == t)
        afters.pop_back();
    }

    if (!marked[t] && S[t] < nextUnique[t] && befores.empty()) {
      //befores should be empty
      //If we have k left, afters should all become marked, so
      //there should be at most k-1 afters, and they all get marked
      if (1 + sz(afters) <= k) {
        k -= 1 + sz(afters);
        marked[t] = true;
        for (int j: afters) marked[j] = true;
        afters.clear();
      }
    }
    if (right[i] != -1) {
      if (!marked[t]) befores.push_back(t);
      dfs(right[i]);
      if (!befores.empty() && befores.back() == t)
        befores.pop_back();
    }
  });
  dfs(0);

  //Output answer
  for (int i = 0; i < n; i++) {
    if (marked[i]) cout << S[i] << S[i];
    else cout << S[i];
  }
  cout << '\n';
}

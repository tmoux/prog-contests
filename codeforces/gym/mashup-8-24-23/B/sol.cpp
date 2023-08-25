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

const int maxn = 2e5+5;
int N, C[maxn];
vector<int> adj[maxn];

vector<int> ans;
ll minCost = 0;
pair<int, vector<int>*> dfs(int i, int p) {
  vector<pair<int, vector<int>*>> v;
  for (int j: adj[i]) {
    if (j == p) continue;
    v.push_back(dfs(j, i));
  }
  sort(all(v));
  vector<int>* r = new vector<int>;
  r->push_back(i);
  if (v.empty()) {
    return {C[i], r};
  }
  else if (sz(v) == 1 || end(v)[-2].first < end(v)[-1].first) {
    F0R(k, sz(v)-1) {
      minCost += v[k].first;
      for (auto j: *v[k].second) ans.push_back(j);
    }
    if (C[i] < v.back().first) return {C[i], r};
    else if (v.back().first < C[i]) return v.back();
    else {
      v.back().second->push_back(i);
      return v.back();
    }
  }
  else {
    F0R(k, sz(v)-1) {
      minCost += v[k].first;
    }
    F0R(k, sz(v)) {
      for (auto j: *v[k].second) ans.push_back(j);
    }
    if (C[i] < v.back().first) return {C[i], r};
    else if (v.back().first < C[i]) return {v.back().first, new vector<int>};
    else return {C[i], r};
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) cin >> C[i];
  REP(N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  auto [c, v] = dfs(0, 0);
  for (auto i: *v) ans.push_back(i);
  minCost += c;

  sort(all(ans));
  cout << minCost << ' ' << sz(ans) << '\n';
  for (auto i: ans) cout << i+1 << ' ';
  cout << '\n';
}

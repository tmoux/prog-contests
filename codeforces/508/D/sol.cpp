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

#define pb push_back
#define f first
#define s second

using vpi = vector<pair<int, int>>;

const int MX = 400005;
int N, M;
vector<vpi> graph(MX); //{ed, edNum}
vector<vpi::iterator> its(MX);
vector<bool> used(MX);

vpi eulerPath(int r) {
  F0R(i, N) its[i] = begin(graph[i]);
  F0R(i, M) used[i] = false;
  vpi ans, s{{r, -1}};
  int lst = -1;
  while (sz(s)) {
    int x = s.back().f; auto &it = its[x], en = end(graph[x]);
    while (it != en && used[it->s]) it++;

    if (it == en) {
      if (lst != -1 && lst != x) return {};
      ans.pb(s.back()); s.pop_back(); if (sz(s)) lst = s.back().f;
    } else {
      s.pb(*it);
      used[it->s] = 1;
    }
  }
  if (sz(ans) != M+1) return {};
  return ans;
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  map<string, int> mp;
  int c = 0;
  vector<string> vs(n);
  map<int, string> S;
  map<int, int> degree;
  F0R(t, n) {
    string s; cin >> s;
    vs[t] = s;
    string a = s.substr(0, 2);
    string b = s.substr(1, 2);
    if (!mp.count(a)) {
      S[c] = a;
      mp[a] = c++;
    }
    if (!mp.count(b)) {
      S[c] = b;
      mp[b] = c++;
    }
    int i = mp[a], j = mp[b];

    graph[i].emplace_back(j, t);
    degree[i]++;
    degree[j]--;
    // cout << i << ' ' << j << endl;
    // graph[j].emplace_back(i, t);
  }

  N = c;
  M = n;
  int start = 0;
  for (int i = 0; i < N; i++) {
    if (degree[i] > 0) {
      start = i;
      break;
    }
  }
  // while (start + 1 < N && degree[start] == 0) start++;
  auto path = eulerPath(start);
  // cout << path << endl;

  if (sz(path) == M+1) {
    string ans = S[path[M].first];
    for (int i = M-1; i >= 0; i--) {
      ans += S[path[i].first][1];
    }
    cout << "YES\n";
    cout << ans << '\n';
  }
  else {
    cout << "NO\n";
  }
}

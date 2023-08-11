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

const int maxn = 1005;
int N;
vector<set<int>> edges[maxn];
vector<set<int>> orig[maxn];
vector<set<int>> recon[maxn];
bool rem[maxn];

void imposs() {
  cout << -1 << '\n';
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  string s;
  getline(cin, s);
  FOR(i, 1, N+1) {
    getline(cin, s);
    // cout << i << ": " << s << endl;
    string tok;
    stringstream ss(s);
    while (getline(ss, tok, '-')) {
      int pos = tok.find(':');
      // int cnt = stoi(tok.substr(0, pos));
      string rest = tok.substr(pos+1);
      // cout << cnt << ' ' << rest << endl;
      stringstream tt(rest);
      string x;
      set<int> S;
      while (getline(tt, x, ',')) {
        int k = stoi(x);
        S.insert(k);
      }
      edges[i].push_back(S);
      // cout << S << endl;
    }
  }
  FOR(i, 1, N+1) orig[i] = edges[i];

  vector<pair<int, int>> ans;
  vector<int> cnt(N+1);
  FOR(i, 1, N+1) cnt[i] = sz(edges[i]);
  REP(N-1) {
    int r = -1;
    FOR(i, 1, N+1) {
      if (rem[i]) continue;
      for (const auto& s: edges[i]) {
        if (sz(s) == 1) {
          r = *s.begin();
          ans.push_back({i, r});
          goto done;
        }
      }
    }
    done:;
    if (r == -1) imposs();
    if (cnt[r] != 1) imposs();
    rem[r] = 1;
    FOR(i, 1, N+1) {
      if (rem[i]) continue;
      for (auto& s: edges[i]) {
        if (s.count(r)) {
          s.erase(r);
          if (s.empty()) cnt[i]--;
        }
      }
    }
  }

  // reconstruct
  vector<vector<int>> adj(N+1);
  for (auto [a, b]: ans) {
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  auto dfs = y_combinator([&](auto dfs, int i, int p, set<int>& s) -> void {
    s.insert(i);
    for (int j: adj[i]) {
      if (j == p) continue;
      dfs(j, i, s);
    }
  });
  FOR(i, 1, N+1) {
    for (int j: adj[i]) {
      set<int> s;
      dfs(j, i, s);
      recon[i].push_back(s);
    }
    sort(all(recon[i]));
    sort(all(orig[i]));
    if (recon[i] != orig[i]) imposs();
  }

  // FOR(i, 1, N+1) {
  //   cout << i << ": " << edges[i] << endl;
  // }

  cout << sz(ans) << '\n';
  for (auto [a, b]: ans) {
    cout << a << ' ' << b << '\n';
  }
}

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

const int maxn = 1e6+6;
int N, M;
vector<int> adj[maxn], dir[maxn];

bool blocked[maxn];
int cnt[maxn];
int in[maxn];

vector<int> F(vector<int> v) {
  if (v.empty()) return {};
  for (auto i: v) in[i] = 1;

  vector<int> S;
  for (auto i: v) {
    if (!blocked[i]) {
      S.push_back(i);
      blocked[i] = 1;
      for (int j: adj[i]) {
        if (in[j]) {
          blocked[j] = 1;
        }
      }
    }
  }
  for (auto i: v) blocked[i] = 0;
  for (auto i: S) {
    cnt[i]++;
    for (int j: dir[i]) {
      cnt[j]++;
    }
  }


  vector<int> T;
  for (auto i: v) {
    if (cnt[i] ==  0) T.push_back(i);
  }

  for (auto i: S) {
    cnt[i]--;
    for (int j: dir[i]) {
      cnt[j]--;
    }
  }
  for (auto i: v) in[i] = 0;
  auto TT = F(T);
  for (auto i: TT) {
    for (int j: dir[i]) {
      cnt[j]++;
    }
  }

  vector<int> res = TT;
  for (auto i: S) {
    if (cnt[i] == 0) res.push_back(i);
  }

  for (auto i: TT) {
    for (int j: dir[i]) {
      cnt[j]--;
    }
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  REP(M) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    dir[a].push_back(b);
  }
  vector<int> v(N); iota(all(v), 1);
  auto ans = F(v);
  cout << sz(ans) << '\n';
  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << '\n';
}

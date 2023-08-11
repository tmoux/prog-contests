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

const int maxn = 3e5+5;
int n;
vector<int> adj[maxn];
int c[maxn];
bool marked[maxn];
int totalC = 0;

int par[maxn];
int total[maxn];
map<int,int> subCount[maxn];

int dfs(int i, int p) {
  par[i] = p;
  if (c[i]) {
    total[i]++;
  }
  for (int j: adj[i]) if (j != p) {
    subCount[i][j] = dfs(j, i);
    total[i] += subCount[i][j];
  }
  return total[i];
}

int getCount(int i, int j) {
  if (j == par[i]) return totalC - total[i];
  else {
    assert(subCount[i].count(j));
    return subCount[i][j];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
    if (c[i]) totalC++;
  }
  REP(n-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs(1, 1);

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (c[i]) {
      marked[i] = true;
      for (int j: adj[i]) if (!marked[j]) {
        marked[j] = true;
        q.push(j);
      }
    }
  }
  while (!q.empty()) {
    int i = q.front(); q.pop();
    for (int j: adj[i]) if (!marked[j]) {
      if (getCount(j, i) >= 2) {
        marked[j] = true;
        q.push(j);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << marked[i] << " \n"[i==n];
  }
}

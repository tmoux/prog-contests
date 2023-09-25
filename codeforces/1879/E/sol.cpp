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

const int maxn = 105;
int N;
vector<int> adj[maxn];
int par[maxn];

int depth[maxn];

void dfs(int i, int d) {
  depth[i] = d;
  for (int j: adj[i]) {
    dfs(j, d+1);
  }
}

int color[maxn];
bool dfs2(int i, int c) {
  color[i] = c;
  bool poss = true;
  if (sz(adj[i]) == 1 && c == 2) {
    poss = false;
  }
  int nc = c == 1 ? 2 : 1;
  for (int j: adj[i]) {
    poss &= dfs2(j, nc);
  }
  return poss;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  for (int i = 2; i <= N; i++) {
    int p; cin >> p;
    par[i] = p;
    adj[p].push_back(i);
  }

  // Case 1: Star with 1 as root.
  if (sz(adj[1]) == N-1) {
    cout << 1 << endl;
    REP(N-1) cout << 1 << ' ';
    cout << endl;
    int x; cin >> x;
    assert(x == 0);
    int e; cin >> e;
    assert(e == 1);
    cout << 1 << endl;
    int res; cin >> res;
    assert(res == 1);
    return 0;
  }

  dfs(1, 0);
  // Case 2: Check if we can bicolor (note: edges to root don't need to be the same.)
  bool can_bicolor = true;
  vector<int> v2;
  for (int j: adj[1]) {
    bool b = dfs2(j, 1);
    if (!b) {
      bool c = dfs2(j, 2);
      if (!c) {
        can_bicolor = false;
        break;
      }
    }
  }

  if (can_bicolor) {
    cout << 2 << endl;
    for (int i = 2; i <= N; i++) {
      cout << color[i] << ' ';
    }
    cout << endl;

    int res;
    while (true) {
      cin >> res;
      if (res == 1) return 0;
      else assert(res == 0);
      vector<int> e(3);

      int c = -1;
      for (int i = 1; i <= 2; i++) cin >> e[i];
      if (e[1] == 1 && e[2] == 1) {
        c = 1;
      }
      else if (e[1] == 1) c = 1;
      else if (e[2] == 1) c = 2;
      assert(c != -1);
      cout << c << endl;
    }

    return 0;
  }

  // Case 3: Else we can always tricolor edges 1-2, 2-3, 3-1.
  cout << 3 << endl;
  for (int i = 2; i <= N; i++) {
    int d = depth[i];
    if (d % 3 == 1) {
      cout << 1 << ' ';
    }
    else if (d % 3 == 2) {
      cout << 2 << ' ';
    }
    else {
      cout << 3 << ' ';
    }
  }
  cout << endl;
  int res;
  while (true) {
    cin >> res;
    if (res == 1) return 0;
    else assert(res == 0);
    vector<int> e(4);

    int c = -1;
    for (int i = 1; i <= 3; i++) cin >> e[i];
    if (e[1] == 0 && e[2] == 0) c = 3;
    else if (e[1] == 0 && e[3] == 0) c = 2;
    else if (e[2] == 0 && e[3] == 0) c = 1;
    else {
      if (e[3] == 0) c = 1;
      else if (e[1] == 0) c = 2;
      else if (e[2] == 0) c = 3;
      else assert(false);
    }
    assert(c != -1);
    cout << c << endl;
  }
}

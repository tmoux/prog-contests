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

const int maxn = 2*(5e5+5);
int N;
vector<int> adj[maxn];

bool vis[maxn];
bool take[maxn];
int sum = 0;
void dfs(int i, int c) {
  vis[i] = 1;
  if (!c) {
    take[i] = 1;
    sum += i;
    sum %= 2*N;
  }
  for (int j: adj[i]) {
    if (!vis[j]) {
      dfs(j, c^1);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  if (N % 2 == 0) {
    cout << "First" << endl;
    F0R(i, 2*N) {
      cout << (i % N) + 1 << ' ';
    }
    cout << endl;
  }
  else {
    cout << "Second" << endl;
    map<int, vector<int>> mp;
    FOR(i, 1, 2*N+1) {
      int p; cin >> p;
      mp[p].push_back(i);
    }
    FOR(i, 1, N+1) {
      assert(sz(mp[i]) == 2);
      adj[mp[i][0]].push_back(mp[i][1]);
      adj[mp[i][1]].push_back(mp[i][0]);
    }
    FOR(i, 1, N+1) {
      adj[i].push_back(i+N);
      adj[i+N].push_back(i);
    }
    FOR(i, 1, 2*N+1) {
      if (!vis[i]) {
        dfs(i, 0);
      }
    }
    if (sum == 0) {
      FOR(i, 1, 2*N+1) {
        if (take[i]) {
          cout << i << ' ';
        }
      }
      cout << endl;
    }
    else {
      FOR(i, 1, 2*N+1) {
        if (!take[i]) {
          cout << i << ' ';
        }
      }
      cout << endl;
    }
  }
}

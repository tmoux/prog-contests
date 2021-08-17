#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
 
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
 
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
 
#define sz(x) (int)(x).size()
#define f first
#define s second
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

const int maxn = 1e5+5;
int n;
set<int> adj[maxn];
bool vis[maxn];

vector<pair<int,int>> adds, removes;

void dfs(int i, int p) {
  vector<int> children;
  for (int j: adj[i]) if (j != p) {
    children.push_back(j);
  }
  for (int j: children) dfs(j,i);
  int cnt = 0;
  for (int j: adj[i]) if (j != p) cnt++;
  if (cnt >= 2) {
    if (i != p && adj[i].count(p)) {
      adj[i].erase(p);
      adj[p].erase(i);
      removes.push_back({i,p});
    }
  }
  int rem = cnt-2;
  vector<int> to_remove;
  for (int j: adj[i]) if (j != p && sz(to_remove) < rem) {
    to_remove.push_back(j);
  }
  for (int j: to_remove) {
    if (adj[i].count(j)) {
      adj[i].erase(j);
      adj[j].erase(i);
      removes.push_back({i,j});
    }
  }
}

void dfs2(int i, int p, int& ret) {
  vis[i] = true;
  ret = i;
  for (int j: adj[i]) if (j != p) {
    dfs2(j,i,ret);
  }
}

void solve() {
  cin >> n;
  F0R(i,n+1) {
    adj[i].clear();
    vis[i] = false;
  }
  F0R(i,n-1) {
    int a, b; cin >> a >> b;
    adj[a].insert(b);
    adj[b].insert(a);
  }
  adds.clear();
  removes.clear();
  dfs(1,1);
  /*
  for (int i = 1; i <= n; i++) {
    cout << i << ": \n";
    for (int j: adj[i]) cout << j << ' ';
    cout << '\n';
  }
  */
  vector<pair<int,int>> bamboos;
  for (int i = 1; i <= n; i++) {
    if (sz(adj[i]) <= 1 && !vis[i]) {
      int a = i;
      int b = a;
      dfs2(a,a,b);
      //cout << a << ' ' << b << '\n';
      bamboos.push_back({a,b});
    }
  }
  for (int i = 0; i < sz(bamboos); i++) {
    adds.push_back({bamboos[i].second,bamboos[i+1].first});
  }
  cout << sz(removes) << '\n';
  F0R(i,sz(removes)) {
    printf("%d %d %d %d\n",removes[i].first,removes[i].second,adds[i].first,adds[i].second);
  }
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}

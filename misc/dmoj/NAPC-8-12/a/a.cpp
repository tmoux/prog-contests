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

const int maxn = 30005;

struct Edge {
  int u, v, c;
};

vector<Edge> adj[maxn];

int n;

int even_count = 0, odd_count = 0;
void dfs(int i, int p, int d) {
  if (d % 2 == 0) even_count++;
  else odd_count++;

  for (Edge& e: adj[i]) {
    if (e.v == p) continue;
    dfs(e.v,i,d+1);
  }
}

void dfs2(int i, int p, int w, int cur, map<int,int>& mp) {
  mp[cur]++;
  for (Edge& e: adj[i]) {
    if (e.v == p) continue;
    int ncur = e.c < w ? cur+1 : cur-1;
    dfs2(e.v,i,w,ncur,mp);
  }
}

map<int,int> getmap(int i, int p, int w) {
  map<int,int> ret;  
  dfs2(i,p,w,0,ret);
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  vector<Edge> edges;
  F0R(i, n-1) {
    int u, v, c; cin >> u >> v >> c;
    edges.push_back({u,v,c}); 
  }
  sort(edges.begin(),edges.end(),[](auto a, auto b) {
      return a.c < b.c;
      });
  int pt = 1;
  map<int,int> mp;
  for (Edge& e: edges) {
    mp[pt] = e.c;
    e.c = pt;
    pt++;
  }
  for (Edge e: edges) {
    adj[e.v].push_back({e.v,e.u,e.c});
    adj[e.u].push_back({e.u,e.v,e.c});
  }

  dfs(1,1,0);
  ll total = even_count * odd_count;

  ll sum = 0;
  for (auto e: edges) {
    map<int,int> lmap = getmap(e.u, e.v, e.c);
    map<int,int> rmap = getmap(e.v, e.u, e.c);

    ll cnt = 0;
    for (auto& p: lmap) {
      if (rmap.count(-p.first)) {
        cnt += 1LL * p.second * rmap[-p.first];
      }
    }
    int weight = mp[e.c];
    //cout << weight << ": " << cnt << '\n';
    //cout << '\n';
    sum += 1LL * weight * cnt;
  }

  double ans = (double)sum/total;
  cout << fixed << setprecision(10) << ans << '\n';
}

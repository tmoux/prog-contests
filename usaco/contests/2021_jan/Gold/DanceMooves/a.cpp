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
#define mp make_pair
#define pb push_back
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
int N, K;
ll M;

set<int> pos[maxn];
set<int> pos2[maxn];

int ans[maxn];

void Union(set<int>& a, set<int>& b) {
  for (auto i: b) {
    a.insert(i);
  }
}

struct Counter {
  vector<int> mp = vector<int>(N+1,0);
  int unique = 0;
  void add(const set<int>& s) {
    for (auto i: s) {
      mp[i]++;
      if (mp[i] == 1) unique++;
    }
  }
  void remove(const set<int>& s) {
    for (auto i: s) {
      mp[i]--;
      if (mp[i] == 0) {
        unique--;
      }
    }
  }
  int countWith(const set<int>& s) {
    int ret = unique;
    for (auto i: s) {
      if (mp[i] == 0) ret++;
    }
    return ret;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K >> M;
  M++;
  int rem = M % K;
  vector<int> a(N+1);
  for (int i = 1; i <= N; i++) {
    pos[i].insert(i);
    if (rem > 0) pos2[i].insert(i);
    a[i] = i;
  }
  for (int i = 0; i < K; i++) {
    int x, y; cin >> x >> y;
    if (i < K-1) {
      pos[a[x]].insert(y);
      pos[a[y]].insert(x);
    }
    if (i < rem-1) {
      pos2[a[x]].insert(y);
      pos2[a[y]].insert(x);
    }
    swap(a[x],a[y]);
  }
  vector<vector<int>> cycles;
  vector<bool> done(N+1,false);
  for (int i = 1; i <= N; i++) {
    if (!done[i]) {
      vector<int> v;
      int idx = i;
      while (!done[idx]) {
        done[idx] = true;
        v.push_back(idx);
        idx = a[idx];
      }
      reverse(v.begin(),v.end());
      cycles.push_back(v);
    }
  }

  Counter c;
  for (auto v: cycles) {
    if (1LL*v.size()*K <= M) {
      //solve all together
      set<int> r;      
      for (int i: v) {
        Union(r,pos[i]);
      }
      for (int i: v) {
        ans[i] = r.size();
      }
    }
    else {
      //M = a*K + b
      int a = M/K;
      int b = M%K;
      auto u = v; 
      u.insert(u.end(),all(v));
      for (int i = 0; i < a; i++) {
        c.add(pos[v[i]]);
      }
      for (int i = 0; i < v.size(); i++) {
        ans[v[i]] = c.countWith(pos2[u[i+a]]);
        c.remove(pos[v[i]]);
        c.add(pos[u[i+a]]);
      }
      for (int i = v.size(); i < v.size()+a; i++) {
        c.remove(pos[u[i]]);
      }
    }
  }

  //output
  for (int i = 1; i <= N; i++) {
    cout << ans[i] << '\n';
  }
}

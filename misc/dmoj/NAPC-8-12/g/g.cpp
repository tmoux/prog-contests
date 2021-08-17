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

const int maxn = 5005;
int N, K;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  vector<int> v(N);
  map<int,int> mp;
  int pt = 0;
  set<int> s;
  F0R(i, N) {
    cin >> v[i];
    s.insert(v[i]);
  }
  for (int i: s) {
    mp[i] = pt++;
  }
  for (int i = 0; i < N; i++) {
    v[i] = mp[v[i]]/K;
  }

  int lis = 0;
  vector<int> dp(N,1);
  for (int i = 0; i < N; i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
      if (v[j] <= v[i]) ckmax(dp[i],dp[j]+1);
    }
    ckmax(lis,dp[i]);
  }

  int ans = N-lis;
  cout << ans << '\n';
}

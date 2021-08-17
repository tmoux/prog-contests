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

const int MOD = 998244353;
const int maxn = 505;
int n;
int val[maxn];

void madd(int& a, int b) {
  a += b;
  if (a > MOD) a -= MOD;
}

int calc(int j) {
  int x = val[j];
  assert(x > 0);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    if (val[i] == -1) {
      a[i] = -1;
    }
    else if (val[i] < x) {
      a[i] = +1;
    }
    else if (val[i] > x) {
      a[i] = 0;
    }
    else {
      assert(val[i] == x);
      if (i < j) {
        a[i] = +1;
      }
      else {
        a[i] = 0;
      }
    }
  }
  vector<vector<int>> dp(2, vector<int>(maxn,0));
  dp[0][0] = 1;
  for (int i = 0; i < n; i++) {
    if (i == j) continue;
    for (int k = 0; k < maxn; k++) {
      madd(dp[1][k],dp[0][k]);
      if (i < j)
        madd(dp[1][max(0,k+a[i])],dp[0][k]);
      else if (0 <= k+a[i])
        madd(dp[1][k+a[i]],dp[0][k]);
    }
    for (int k = 0; k < maxn; k++) {
      dp[0][k] = dp[1][k];
      dp[1][k] = 0;
    }
  }
  int res = 0;
  for (int k = 0; k < maxn; k++) {
    madd(res,dp[0][k]);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++) {
    char c; cin >> c;
    if (c == '-') {
      val[i] = -1;
    }
    else {
      int x; cin >> x;
      val[i] = x;
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (val[i] > 0) {
      int cnt = calc(i);
      int add = (1LL*val[i]*cnt) % MOD;
      //cout << val[i] << ": " << cnt << endl;
      madd(ans,add);
    }
  }
  cout << ans << '\n';
}

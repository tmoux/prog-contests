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

const int maxn = 405;
int n, M;

void madd(int& a, int b) {
  a += b;
  if (a >= M) a -= M;
}
int mult(int a, int b) {
  return (1LL*a*b) % M;
}

int choose[maxn][maxn];
int pow2[maxn];

int dp[maxn][maxn];

int f(int i, int j) {
  if (i < 0) return 0;
  if (i == 0) return j == 0 ? 1 : 0;
  int& res = dp[i][j];
  if (res != -1) return res;
  res = 0;
  for (int k = 1; k <= j; k++) {
    //# of ways to make a segment of k using k steps is 2^{k-1}
    int add = mult(pow2[k-1],choose[j][k]);
    add = mult(add,f(i-k-1,j-k));
    madd(res,add);
  }
  return res;
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> M;
  choose[0][0] = 1;
  for (int i = 1; i < maxn; i++) {
    choose[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      madd(choose[i][j],choose[i-1][j-1]);
      madd(choose[i][j],choose[i-1][j]);
    }
  }
  pow2[0] = 1;
  for (int i = 1; i < maxn; i++) {
    pow2[i] = mult(pow2[i-1],2);
  }
  memset(dp,-1,sizeof dp);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    cout << i << ": " << f(n+1,i) << '\n';
    madd(ans,f(n+1,i));
  }
  cout << ans << '\n';
}

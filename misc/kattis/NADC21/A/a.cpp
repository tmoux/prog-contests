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
const int maxn = 10;
int n;
int T[maxn];
//T[0] = 60, T[1] = 60, T[2] = 24

int dig(int x) {
  return (x/10)%10;
}
ll dp[maxn][100];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  for (int i = n-1; i >= 0; i--) {
    cin >> T[i];
  }
  //memset(dp,-1,sizeof dp);
  for (int i = 0; i < T[0]; i++) {
    dp[0][i]++;
  }
  for (int i = 1; i < n; i++) {
    for (int a1 = 0; a1 < T[i]; a1++) {
      int b = a1%10;
      for (int a2 = 0; a2 < 100; a2++) {
        int c = (a2/10)%10;
        int d = a2%10;
        if (b*10+c < T[i-1] && b*10+d < T[i-1]) {
          dp[i][a1] += dp[i-1][a2];
        }
      }
    }
    /*
    cout << "dp " << i << '\n';
    for (int j = 0; j < 100; j++) {
      cout << j << ": " << dp[i][j] << '\n';
    }
    */
  }
  ll ans = 0;
  for (int j = 0; j < 100; j++) {
    ans += dp[n-1][j];
  }
  ll total = 1;
  for (int i = 0; i < n; i++) total *= 1LL*T[i];
  cout << total-ans << '\n';
}

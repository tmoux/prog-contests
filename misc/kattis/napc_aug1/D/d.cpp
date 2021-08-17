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

const int maxn = 550;
int n, m;
bool seen[maxn][maxn];

int up[maxn][maxn], down[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      up[i][j] = n+1;
      down[i][j] = 0;
    }
  }
  ll ans = (1LL*n*(n+1)/2) * (1LL*m*(m+1)/2);
  int cnt = 0;
  F0R(_, m*n) {
    int a, b; cin >> a >> b;

    for (int i = b, top = n, bot = 1; i >= 1; i--) {
      if (seen[a][i]) break;
      ckmin(top, up[a][i]-1);
      ckmax(bot, down[a][i]+1);
      for (int j = b, rtop = top, rbot = bot; j <= m; j++) {
        if (seen[a][j]) break;
        cnt++;
        ckmin(rtop, up[a][j]-1);
        ckmax(rbot, down[a][j]+1);
        ll sub = 1LL*(rtop-a+1)*(a-rbot+1);
        ans -= sub;
      }
    }

    for (int i = a-1; i >= 1; i--) {
      if (seen[i][b]) break;
      up[i][b] = a;
    }
    for (int i = a+1; i <= n; i++) {
      if (seen[i][b]) break;
      down[i][b] = a;
    }
    seen[a][b] = true;
    cout << ans << '\n';
  }

  cout << "cnt= " << cnt << endl;
}

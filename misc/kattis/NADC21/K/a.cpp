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
const int maxx = 8e6+60;
int N, K;
int p[maxn], d[maxn];
int pop[maxx];

const int C = 30;

double dp[maxn][2*C];
int cnt[maxn];

double pow2inv[2*C];
double pc[maxn][2*C];
double calc(int x, int last) {
  int m = ((x-last)+x)/2+1;
  double ret = 0;
  for (int i = m; i < x+C; i++) {
    ret += pow2inv[abs(x-i)]*pop[i];
  }
  return ret;
}

void compute(double L) {
  //compute dp and cnt
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 2*C; j++) {
      dp[i][j] = 0;
    }
    cnt[i] = 0;
  }
  for (int j = 1; j < 2*C; j++) {
    dp[0][j] = pc[0][j] - L;
  }
  for (int i = 1; i < N; i++) {
    for (int j = 1; j < 2*C; j++) {
      dp[i][j] = pc[i][j];
      ckmax(dp[i][j],dp[i-1][j-1]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  pow2inv[0] = 1;
  for (int i = 1; i < 2*C; i++) {
    pow2inv[i] = pow2inv[i-1]*0.5;
  }
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    cin >> p[i] >> d[i];
    pop[d[i]] = p[i];
  }
  //precalc
  for (int i = 0; i < N; i++) {
    for (int j = 1; j < 2*C; j++) {
      pc[i][j] = calc(d[i],j);
      cout << i << ' ' << j << ": " << pc[i][j] << '\n';
    }
  }

  double lo = 0, hi = 1e18;
  F0R(_,100) {
    double L = (lo+hi)/2;
    compute(L);
    if (cnt[N-1] <= K) {
      lo = L;
    }
    else {
      hi = L;
    }
  }
  compute(lo);
  //double ans = dp[N-1] + cnt[N-1] * lo;
  //cout << fixed << setprecision(10) << ans << '\n';
}

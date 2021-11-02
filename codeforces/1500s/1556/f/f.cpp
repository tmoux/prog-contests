#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

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

const int maxn = 14, MOD = 1e9+7;

void madd(int& a, int b) {
  a += b;
  if (a > MOD) a -= MOD;
}
void msub(int& a, int b) {
  madd(a, MOD-b);
}
int mult(int a, int b) {
  return (1LL*a*b) % MOD;
}
int modexp(int a, int b) {
  int res = 1;
  while (b) {
    if (b&1) res = mult(res, a);
    a = mult(a, a);
    b >>= 1;
  }
  return res;
}
int inverse(int x) {
  return modexp(x, MOD-2);
}
int mdiv(int a, int b) {
  return mult(a, inverse(b));
}

int n, a[maxn], p[maxn][maxn];

int all_beaten_dp[1<<maxn][maxn];
int all_beaten(int mask, int j) {
  int& res = all_beaten_dp[mask][j];
  if (res != -1) return res;
  res = 1;
  F0R(i, n) {
    if (mask & (1<<i))
      res = mult(res, p[i][j]);
  }
  return res;
}

int all_beats(int mask1, int mask2) {
  int res = 1;
  F0R(i, n) {
    if (mask2 & (1<<i))
      res = mult(res, all_beaten(mask1, i));
  }
  return res;
}

int strong_dp[1<<maxn];
int strong(int mask) {
  int& res = strong_dp[mask];
  if (res != -1) return res;
  res = 1;
  for (int submask = mask; submask; submask = (submask-1) & mask) {
    if (submask == mask) continue;
    msub(res, mult(strong(submask), all_beats(submask, mask^submask)));
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  memset(strong_dp, -1, sizeof strong_dp);
  memset(all_beaten_dp, -1, sizeof all_beaten_dp);

  cin >> n;
  F0R(i, n) cin >> a[i];
  F0R(i, n) {
    F0R(j, n) {
      p[i][j] = mdiv(a[i], a[i]+a[j]);
    }
  }

  int ans = 0;
  int all = (1<<n)-1;
  for (int mask = 1; mask < (1<<n); mask++) {
    int size = __builtin_popcount(mask);
    int prob = mult(strong(mask), all_beats(mask, mask^all));
    //cout << mask << ' ' << strong(mask) << ' ' << all_beats(mask, mask^all)  << endl;
    int add = mult(size, prob);
    madd(ans, add);
  }
  cout << ans << '\n';
}

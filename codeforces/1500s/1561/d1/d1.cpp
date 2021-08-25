#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;
 
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

const int maxn = 4e6+5, logn = 19;
int n, MOD;

void madd(int& a, int b) {
  a += b;
  if (a > MOD) a -= MOD;
}
int mult(int a, int b) {
  return (1LL * a * b) % MOD;
}

int dp[logn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> MOD;

  dp[0][n] = 1;
  int ans = 0;
  for (int d = 0; d < logn; d++) {
    int sum = 0;
    for (int i = n; i >= 1; i--) {
      madd(sum, dp[d][i+1]);
      madd(dp[d][i], sum);
    }
    madd(ans, dp[d][1]);
    if (dp[d][1] == 0) break;

    //push divisions to next layer
    for (int i = n; i >= 1; i--) {
      if (dp[d][i] > 0) {
        cout << d << ": " << i << endl;
        break;
      }
    }
    for (int i = n; i >= 1; i--) {
      if (dp[d][i] == 0) continue;

      int mxz = 1;
      for (int z = 2; z*z < i; z++) {
        mxz = z;
        madd(dp[d+1][i/z], dp[d][i]);
      }

      for (int z = 1; z*z <= i; z++) {
        int cnt = max(0, i/z - max(mxz, i/(z+1)));
        madd(dp[d+1][z], mult(cnt, dp[d][i]));
      }

      /*
      for (int& z: small_z[i]) {
        madd(dp[d+1][z], dp[d][i]);
      }
      for (auto& p: big_z[i]) {
        madd(dp[d+1][p.first], mult(p.second, dp[d][i]));
      }
      */
    }
  }
  cout << ans << '\n';
}

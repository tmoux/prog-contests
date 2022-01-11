#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
// }}}

class KnapsackTweak {
public:
  int ceil(int a, int b) {
    return (a+b-1)/b;
  }
  int smallest(vector<int> items, int target) {
    int N = sz(items);
    const int MX = 300100;
    vector<bitset<MX>> dp(N+1);
    vector<bitset<MX>> ndp(N+1);

    dp[0][0] = true;
    F0R(i, N) {
      ndp = dp;

      for (int j = 0; j+1 <= N; j++) {
        ndp[j+1] |= dp[j] << items[i];
      }

      dp = ndp;
    }

    int X = target;
    for (int i = 1; i <= N; i++) {
      for (int k = 0; k < MX; k++) {
        if (dp[i][k]) {
          ckmin(X, ceil(abs(target - k), i));
        }
      }
    }

    sort(all(items));
    int smallsum = 0;
    for (int i = 0; i < N; i++) {
      smallsum += items[i];
      ckmin(X, ceil(abs(target - smallsum), i+1));
    }

    return X;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  KnapsackTweak test;
  vector<int> v;
  for (int i = 0; i < 50; i++) {
    v.push_back(100000);
  }
  int T = 86302;
  cout << test.smallest(v, T) << endl;
}

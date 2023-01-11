#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
// }}}

class TallyMarksSystem {
public:
  int construct(int N) {
    const int maxk = 21;
    vector<vector<int>> opt(maxk);
    const int INF = 1e9;
    vector<int> dp(N + 1, INF);
    dp[0] = 0, dp[1] = dp[5] = 1;
    opt[1].push_back(1);
    opt[1].push_back(5);
    for (int i = 2; i < maxk; i++) {
      for (int a = 1; a < i; a++) {
        int b = i - a;
        cout << opt[a].size() * opt[b].size() << endl;
        for (int x: opt[a]) {
          for (int y: opt[b]) {
            if (x + y <= N && dp[x+y] == INF) {
              dp[x+y] = i;
              opt[i].push_back(x+y);
            }
            if (1LL * x * y <= N && dp[x*y] == INF) {
              dp[x*y] = i;
              opt[i].push_back(x*y);
            }
          }
        }
      }
    }
    return dp[N];
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  TallyMarksSystem test;
  int N; cin >> N;
  cout << test.construct(N) << endl;
  // cout << test.construct(N) << ' ' << test.construct2(N) << endl;
}

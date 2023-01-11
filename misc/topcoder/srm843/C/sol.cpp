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

class Component {
  int N, S;
  map<vector<int>, double> dp;
  double rec(vector<int> v) {
    if (dp.count(v)) return dp[v];
    if (v[N] == 1) return dp[v] = 1.0;
    bool done = true;
    for (int i = 1; i < S; i++) if (v[i]) done = false;
    if (done) return dp[v] = 1.0;

    int total = N * (N - 1) / 2;
    for (int i = 1; i < N; i++) {
      total -= v[i] * (i * (i - 1) / 2);
    }

    double ans = 0;
    for (int i = 1; i < N; i++) {
      {
        if (v[i] >= 2 && i+i != S) {
          int numEdges = (v[i] * i * (v[i] - 1) * i) / 2;
          v[i] -= 2;
          v[i+i]++;

          ans += (double) numEdges / total * rec(v);

          v[i+i]--;
          v[i] += 2;
        }
      }
      for (int j = i+1; j < N; j++) {
        if (i+j != S && v[i] > 0 && v[j] > 0) {
          int numEdges = v[i] * i * v[j] * j;
          v[i]--;
          v[j]--;
          v[i+j]++;

          ans += (double) numEdges / total * rec(v);

          v[i]++;
          v[j]++;
          v[i+j]--;
        }
      }
    }
    return dp[v] = ans;
  }
public:
  double solve(int _N, int _S) {
    N = _N;
    S = _S;

    if (S == 1) return 1.0;

    vector<int> v(N+1); v[1] = N;
    double ans = rec(v);
    return 1 - ans;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  Component test;
  int N, S; cin >> N >> S;
  cout << test.solve(N, S) << '\n';
}

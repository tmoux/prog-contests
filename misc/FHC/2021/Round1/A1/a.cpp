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

int solve() {
  int n; cin >> n;
  string s; cin >> s;
  const int INF = 1e9;
  vector<vector<int>> dp(n+1, vector<int>(2, 0));
  for (int i = 0; i < n; i++) {
    if (s[i] == 'F') {
      dp[i+1][0] = dp[i][0];
      dp[i+1][1] = dp[i][1];
    }
    else if (s[i] == 'O') {
      dp[i+1][0] = INF;
      dp[i+1][1] = min(dp[i][0]+1, dp[i][1]);
    }
    else {
      dp[i+1][0] = min(dp[i][0], dp[i][1]+1);
      dp[i+1][1] = INF;
    }
  }
  return min(dp[n][0], dp[n][1]);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}

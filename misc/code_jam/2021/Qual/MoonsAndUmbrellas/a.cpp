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
#define pb push_back
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

//CC : 0
//CJ : X
//JC : Y
//JJ : 0

const int INF = 1e9;
//0 = #, 1 = C, 2 = J
int calc(int prev, int post, int len, int X, int Y) {
  vector<vector<int>> dp(len+2,vector<int>(3,INF));
  dp[0][prev] = 0;
  for (int i = 1; i < len+2; i++) {
    for (int c : {0,1,2}) {
      if (c == 0 && i < len+1) continue;
      for (int d : {0,1,2}) {
        int tr = dp[i-1][d];
        if (d == 1 && c == 2) tr += X;
        else if (d == 2 && c == 1) tr += Y;
        ckmin(dp[i][c],tr);
      }
    }
  }
  return dp[len+1][post];
}

map<char,int> mp = {
  {'#',0},
  {'C',1},
  {'J',2}
};

int solve() {
  int X, Y; cin >> X >> Y;
  string S; cin >> S;
  S = '#' + S + '#';
  int ans = 0;
  for (int i = 1; i < (int)S.size()-1; i++) {
    if (S[i] == '?') {
      char prev = S[i-1];
      int start = i;
      while (S[i] == '?') i++;
      char post = S[i];
      //cout << prev << ' ' << post << ' ' << i-start << ": " << calc(mp[prev],mp[post],i-start,X,Y) << '\n';
      ans += calc(mp[prev],mp[post],i-start,X,Y);
      i--;
    }
    else if (S[i] == 'C' && S[i+1] == 'J') ans += X;
    else if (S[i] == 'J' && S[i+1] == 'C') ans += Y;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}

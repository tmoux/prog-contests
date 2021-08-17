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

void amin(int& a, int b) {
  a = min(a,b);
}
void amax(int& a, int b) {
  a = max(a,b);
}

const int INV = -1e9;
const int maxn = 1e3+3;
int n;
int dp[maxn][maxn][2][2][2];

//A - B, A trying to minimize, B trying to maximize
int f(int i, int j, int rev, int turn, int mid) {
  int& res = dp[i][j][rev][turn][mid];
  if (res != INV) return res;
  if (i == 0 && j == 0 && mid == 1) {
    //printf("[%d][%d][%d][%d][%d]: %d\n",i,j,rev,turn,mid,0);
    return res = 0;
  }
  if (turn == 0) { //Alice
    res = maxn;
    //try mid
    if (mid == 0) amin(res,f(i,j,0,1,1)+1);
    //turn unpaired 0 -> 1
    if (i > 0) amin(res,f(i-1,j,0,1,mid)+1);
    //turn paired 0 -> 1
    if (j > 0) amin(res,f(i+1,j-2,0,1,mid)+1);
    //reverse
    if (i > 0 && rev == 0) amin(res,f(i,j,1,1,mid));
  }
  else { //Bob
    res = -maxn;
    //try mid
    if (mid == 0) amax(res,f(i,j,0,0,1)-1);
    //turn unpaired 0 -> 1
    if (i > 0) amax(res,f(i-1,j,0,0,mid)-1);
    //turn paired 0 -> 1
    if (j > 0) amax(res,f(i+1,j-2,0,0,mid)-1);
    //reverse
    if (i > 0 && rev == 0) amax(res,f(i,j,1,0,mid));
  }
  //printf("[%d][%d][%d][%d][%d]: %d\n",i,j,rev,turn,mid,res);
  return res;
}

void solve() {
  cin >> n;
  string s; cin >> s;
  int i = 0, j = 0;
  for (int k = 0; k < n/2; k++) {
    int c = (s[k] == '0') + (s[n-1-k] == '0');
    if (c == 1) i++;
    else if (c == 2) j += 2;
  }
  int hasMid = (n % 2 == 1) && (s[n/2] == '0') ? 0 : 1;
  int ans = f(i,j,0,0,hasMid);
  //cout << "ans = " << ans << '\n';
  if (ans < 0) {
    cout << "ALICE\n";
  }
  else if (ans == 0) {
    cout << "DRAW\n";
  }
  else if (ans > 0) {
    cout << "BOB\n";
  }
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie(NULL);
  F0R(i,maxn) F0R(j,maxn) F0R(rev,2) F0R(turn,2) F0R(mid,2) {
    dp[i][j][rev][turn][mid] = INV;
  }
  int t; cin >> t;
  while (t--) solve();
}

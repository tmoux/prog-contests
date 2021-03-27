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
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define DEBUG(x) cerr << #x << ": " << x << '\n'
#define DEBUG2(x,y) cerr << #x << ": " << x << ", " << #y << ": " << y << '\n'
#define DEBUG3(x,y,z) cerr << #x << ": " << x << ", " << #y << ": " << y << ", " << #z << ": " << z << '\n';
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

int ask(int a, int b, int c) {
  cout << a << ' ' << b << ' ' << c << endl;
  int x; cin >> x;
  assert(x != -1);
  return x;
}
void answer(vector<int> v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i];
    if (i < v.size()-1) cout << ' ';
  }
  cout << endl;
  int x; cin >> x;
  assert(x == 1);
}

// 0   1   2
//[0,1] -> 0, 1
//[0,2] -> 1, 1
//[0,3] -> 1, 2

void calc(int i, int lo, int hi, vector<int>& ord) {
  if (lo == hi) {
    ord.insert(ord.begin()+lo+1,i);
    return;
  }
  //DEBUG2(lo,hi);
  int d = hi-lo+1;
  int L = lo + d/3;
  int R = hi - d/3;
  if (L == R) R++;
  //DEBUG3(ord[L],i,ord[R]);
  int x = ask(ord[L],i,ord[R]);
  if (x == i) {
    //L < i < R
    if (lo == L && R == hi) {
      ord.insert(ord.begin()+L+1,i);
    }
    else {
      if (L+1 < R) L++;
      if (R-1 > L) R--;
      calc(i,L,R,ord);
    }
  }
  else if (x == ord[L]) {
    //i < L < R
    if (lo == L) {
      ord.insert(ord.begin()+L,i);
    }
    else {
      if (L-1 > lo) L--;
      calc(i,lo,L,ord);
    }
  }
  else if (x == ord[R]) {
    //L < R < i
    if (hi == R) {
      ord.insert(ord.begin()+R+1,i);
    }
    else {
      if (R+1 < hi) R++;
      calc(i,R,hi,ord); 
    }
  }
  else assert(false);
}

void solve(int N) {
  vector<int> ord;
  int x = ask(1,2,3);
  if (x == 1) ord = {2,1,3};
  else if (x == 2) ord = {1,2,3};
  else if (x == 3) ord = {1,3,2};
  //DEBUG(ord);
  for (int i = 4; i <= N; i++) {
  //for (int i = N; i >= 4; i--) {
    calc(i,0,ord.size()-1,ord);
    //DEBUG(ord);
  }
  answer(ord);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T, N, Q; cin >> T >> N >> Q;
  for (int tc = 1; tc <= T; tc++) {
    solve(N);
  }
}

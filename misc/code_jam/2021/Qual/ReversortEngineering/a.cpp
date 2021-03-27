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
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

int check(vector<int> a) {
  int ans = 0;
  int N = a.size();
  for (int i = 0; i < N-1; i++) {
    int idx = i;
    int mn = N+1;
    for (int j = i; j < N; j++) {
      if (ckmin(mn,a[j])) idx = j;
    }
    reverse(a.begin()+i,a.begin()+idx+1);
    ans += idx-i+1;
  }
  return ans;
}

//N-1 <= C <= N*(N+1)/2-1
//0 <= C' <= N*(N+1)/2-1-(N-1)
void solve() {
  int N, C; cin >> N >> C;
  if (!(N-1 <= C && C <= N*(N+1)/2-1)) {
    cout << "IMPOSSIBLE\n";
    return;
  }
  else {
    vector<int> atIdx(N,-1);
    vector<int> a(N);
    iota(all(a),0);
    C -= N-1;
    for (int i = 0; i < N; i++) {
      int idx = min(C,N-1-i);
      C -= idx;
      //cout << i << ": " << idx << '\n';
      atIdx[a[i+idx]] = i+1;
      reverse(a.begin()+i,a.begin()+i+idx+1);
    }
    //cout << check(atIdx) << '\n';
    //assert(check(atIdx) == C+(N-1));
    for (int i = 0; i < N; i++) {
      cout << atIdx[i] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": ";
    solve();
  }
}

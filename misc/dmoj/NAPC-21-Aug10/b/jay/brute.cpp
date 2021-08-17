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

const int maxn = 1005;
int n;

int deg[maxn];

const int max_sec = 8640;
const int FAC = 1200;
const int ONE_REV = 360 * FAC;
int recharge_time;

int degrees_to_sec(int x) {
  return (x*12+(FAC-1))/FAC;
  //return int(ceil(x*12/(double)FAC));
}

int calc(const vector<int>& perm) {
  int tot = 0;
  int curr = deg[perm[0]];
  int recharge_to_degrees = recharge_time/12;
  for (int i = 0; i < n; i++) {
    int add = deg[perm[i]]-curr;
    if (add < 0) add += ONE_REV;
    tot += add + recharge_to_degrees;
    curr = (deg[perm[i]] + recharge_to_degrees) % ONE_REV;
  }
  return tot;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;

  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    double d; cin >> d;
    deg[i] = d*FAC;
  }
  cin >> recharge_time;
  recharge_time *= FAC;

  vector<int> best;
  vector<int> perm;
  int ans = 2e9;
  F0R(i, n) perm.push_back(i);
  do {
    if (ckmin(ans, degrees_to_sec(calc(perm)))) {
      best = perm;
    }
    //cout << degrees_to_sec(calc(perm)) << '\n';
  } while (next_permutation(perm.begin(), perm.end()));

  if (ans > max_sec) {
    cout << "not possible\n";
  }
  else {
    F0R(i, n) {
      cout << (double)deg[perm[i]]/FAC << ' ';
    }
    cout << '\n';
    cout << ans << '\n';
  }
}

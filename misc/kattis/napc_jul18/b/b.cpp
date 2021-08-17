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

const int maxk = 20005;
const ll INF = 8e18;
ll N;
ll T;
int K;
ll c[maxk];

//Return the number of people that can be done with cost <= C.
ll countWithCost(ll C, int k) {
  ll res = 0;
  for (int i = 0; i < k; i++) {
    ll d = max(0LL,(C-c[i])/T + 1);
    ll sq = 2*d*(d+1)+1;
    res += max(0LL,sq-2);
  }
  //cout << C << ": " << res << endl;
  return res;
}

ll calcWithFloors(int k) {
  ll ans = 0;
  ll n = N;
  for (int i = 0; i < k; i++) {
    if (n > 0) {
      ans += c[i];
      n--;
    }
  }

  ll lo = 0, hi = 2e6*T + 2e9;
  while (lo + 1 < hi) {
    ll mid = (lo+hi)/2;
    ll cnt = countWithCost(mid, k);
    if (cnt <= n) {
      lo = mid;
    }
    else {
      hi = mid;
    }
  }
  ll cost = lo;
  assert(countWithCost(cost+1, k) > n);

  for (int i = 0; i < k; i++) {
    for (int d = 1; (d-1)*T + c[i] <= cost; d++) {
      ll cur_cost = (d-1)*T + c[i];
      ll num = d == 1 ? 3 : 4*d;
      ans += num*cur_cost;
      n -= num;
      assert(n >= 0);
    }
  }
  
  ans += (cost+1)*n;
  assert (ans > 0);
  return ans;
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> T >> K;
  for (int i = 0; i < K; i++) {
    cin >> c[i];
  }
  N = 1e9;
  T = 500000;
  K = 200;
  for (int i = 0; i < K; i++) c[i] = i + 5;

  int lo = 0, hi = K;
  while (hi - lo > 1) {
    int mid = (lo+hi)/2;
    //printf("%d: %lld, %d: %lld\n", mid, calcWithFloors(mid), mid+1, calcWithFloors(mid+1));
    if (calcWithFloors(mid) < calcWithFloors(mid+1))
      hi = mid;
    else
      lo = mid;
  }
  ll ans = calcWithFloors(lo+1);
  cout << ans << '\n';
}

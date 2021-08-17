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

int calc(int start) {
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < n; i++) {
    if (deg[i] < start) pq.push(deg[i]+ONE_REV);
    else pq.push(deg[i]);
  }
  int recharge_to_degrees = recharge_time/12;

  int cur_degree = start;
  while (!pq.empty()) {
    int f = pq.top(); pq.pop();
    assert(cur_degree <= f);
    cur_degree = f + recharge_to_degrees;

    while (!pq.empty() && pq.top() < cur_degree) {
      int newf = pq.top() + ONE_REV;
      pq.pop();
      pq.push(newf);
    }
  }
  return cur_degree-start;
}

int degrees_to_sec(int x) {
  return int(ceil(x*12/(double)FAC));
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

  int ans = max_sec + 1;
  for (int i = 0; i < n; i++) {
    //cout << deg[i] << ": " << degrees_to_sec(calc(deg[i])) << '\n';
    ckmin(ans, degrees_to_sec(calc(deg[i])));
  }
  if (ans > max_sec) {
    cout << "not possible\n";
  }
  else {
    cout << ans << '\n';
  }
}

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

int sqr(int x) {
  return x*x;
}
int dist(pi a, pi b) {
  return sqr(a.f-b.f) + sqr(a.s-b.s);
}

pi minu(pi a, pi b) {
  return {a.f-b.f,a.s-b.s};
}

pi operator+(pi a, pi b) {
  return {a.f+b.f,a.s+b.s};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  pi a, b, c; 
  cin >> a.f >> a.s;
  cin >> b.f >> b.s;
  cin >> c.f >> c.s;
  pi ans;
  if (dist(a,b) == dist(a,c)) {
    ans = a+minu(b,a)+minu(c,a);
  }
  else if (dist(b,a) == dist(b,c)) {
    ans = b+minu(a,b)+minu(c,b);
  }
  if (dist(c,a) == dist(c,b)) {
    ans = c+minu(a,c)+minu(b,c);
  }
  cout << ans.f << ' ' << ans.s << '\n';
}

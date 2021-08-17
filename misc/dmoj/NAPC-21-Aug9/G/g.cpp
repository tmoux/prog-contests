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
int w, n;

struct Circle {
  int x, y, r;
} circles[maxn];

double dist[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  F0R(tc, T) {
    cin >> w >> n;
    for (int i = 0; i < n; i++) {
      cin >> circles[i].x >> circles[i].y >> circles[i].r;
    }
    F0R(i, n) {
      F0R(j, n) {
        dist[i][j] = hypot(circles[i].x-circles[j].x, circles[i].y-circles[j].y) - circles[i].r - circles[j].r;
      }
    }
    double lo = 0, hi = w;
    F0R(_, 70) {
      double inflate = (lo+hi)/2;
      vector<bool> seen(n,false);
      queue<int> q;
      for (int i = 0; i < n; i++) {
        if (circles[i].x-circles[i].r-inflate < 0) {
          q.push(i);
        }
      }
      bool poss = true;
      while (!q.empty()) {
        int i = q.front(); q.pop();
        if (!seen[i]) {
          seen[i] = true;
          if (circles[i].x+circles[i].r+inflate > w) {
            poss = false;
          }
          for (int j = 0; j < n; j++) {
            if (dist[i][j]-inflate < 0) {
              q.push(j);
            }
          }
        }
      }
      (poss ? lo : hi) = inflate;
    }
    cout << fixed << setprecision(10) << lo/2 << '\n';
  }
}

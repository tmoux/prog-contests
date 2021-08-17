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
struct pt {
    double x, y;
};

struct line {
    double a, b, c;
};

const double EPS = 1e-9;

int sgn(int x) {
  if (abs(x) < EPS) return 0;
  else if (x < 0) return -1;
  else return 1;
}

bool comp(int x, int y) {
  return x == 0 || y == 0 || x == y;
}

bool mid (double x1,
          double y1,
          double x2,
          double y2,
          double x3,
          double y3) {
  return min(x1,x2) <= x3 && x3 <= max(x1,x2) &&
         min(y1,y2) <= y3 && y3 <= max(y1,y2);
}

bool same(double x1,
          double y1,
          double x2,
          double y2,
          double x3,
          double y3) {
  return comp(sgn(x3-x2),sgn(x2-x1)) &&
         comp(sgn(y3-y2),sgn(y2-y1));
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  double x1, y1, x2, y2, x3, y3, x4, y4;
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
  double D = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
  if (abs(D) < EPS) {
    cout << -1 << '\n';
  }
  else {
    /*
    double px = ((x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4))/D;
    double py = ((x1*y2-y1*x2)*(y3-y4)-(y1-y2)*(x3*y4-y3*x4))/D;
    cout << (int)floor(px) << ' ' << (int)floor(py) << '\n';
    */
    //double t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
    //double u = ((x2-x1)*(y1-y3)-(y2-y1)*(x1-x3))/((x1-x2)*(y3-y4)*(y1-y2)*(x3-x4));
    //cout << t << ' ' << u << '\n';
    double px = ((x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4))/D;
    double py = ((x1*y2-y1*x2)*(y3-y4)-(y1-y2)*(x3*y4-y3*x4))/D;
    // cout << px << ' ' << py << '\n';
    if ((mid(x1,y1,x2,y2,px,py) || same(x1,y1,x2,y2,px,py)) &&
        (mid(x3,y3,x4,y4,px,py) || same(x3,y3,x4,y4,px,py))) {
      cout << (int)floor(px) << ' ' << (int)floor(py) << '\n';
    }
    else {
      cout << -1 << '\n';
    }
    /*
    if (isok(x1,y1,x2,y2,x3,y3,x4,y4) &&
        isok(x3,y3,x4,y4,x1,y1,x2,y2)) {
      //cout << (int)floor(t) << ' ' << (int)floor(u) << '\n';
      double px = ((x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4))/D;
      double py = ((x1*y2-y1*x2)*(y3-y4)-(y1-y2)*(x3*y4-y3*x4))/D;
      cout << (int)floor(px) << ' ' << (int)floor(py) << '\n';
    }
    else {
      cout << -1 << '\n';
    }
    */
  }
}

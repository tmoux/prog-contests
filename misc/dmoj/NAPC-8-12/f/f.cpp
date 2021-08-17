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

const int maxn = 50005;
int N, K;
struct Point {
  int x, y, k;

  bool operator<(const Point& rhs) const {
    return x < rhs.x;
  }
} points[maxn];

double dist(const Point& a, const Point& b) {
  return hypot(a.x-b.x, a.y-b.y);
}

unsigned int mergeSums(unsigned int a, unsigned int b) {
  unsigned int res = a | b;
  F0R(i, K) {
    if (a & (1<<i)) {
      //res |= (b<<i & ((1<<K)-1)) | (b>>(K-i));
      res |= (b<<i) | (b>>(K-i));
    }
  }
  return res;
}

string getmask(unsigned int a) {
  string r = "";
  F0R(i, 30) {
    if (a & (1<<i)) r += '1';
    else r += '0';
  }
  return r;
}

unsigned int sums[maxn]; //reset
int parent[maxn]; //memset to -1
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) {
      swap(sums[x],sums[y]);
      swap(x,y);
    }
    sums[x] = mergeSums(sums[x],sums[y]);
    parent[x] += parent[y];
    parent[y] = x;
}

bool check(double D) {
  F0R(i, N) {
    parent[i] = -1;
    sums[i] = 1<<points[i].k;
  }

  int lt = 0;
  set<pair<int,int>> curr; //y-coord, id
  F0R(i, N) {
    while (points[lt].x < points[i].x - D) {
      //remove point lt
      curr.erase({points[lt].y,lt});
      lt++;
    }

    int Y = points[i].y;
    for (auto it = curr.lower_bound({Y-D,0}); it != curr.end() && it->first <= Y+D; ++it) {
      int id = it->second;
      if (dist(points[i],points[id]) <= D) {
        Union(i,id);

        //cout << i << ": " << getmask(sums[Find(i)]) << '\n';

        if (sums[Find(i)] & 1) return true;
      }
    }
    curr.insert({points[i].y,i});
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  F0R(i, N) {
    cin >> points[i].x >> points[i].y >> points[i].k;
    points[i].k %= K;
    assert(points[i].k != 0);
  }
  sort(points,points+N);

  double lo = 0.0, hi = 2e8;
  F0R(_, 60) {
    double mid = (lo+hi)/2;
    (check(mid) ? hi : lo) = mid;
  }
  cout << fixed << setprecision(3) << lo << '\n';
  /*
  unsigned int a = 1<<5;
  unsigned int b = 1<<6;
  cout << getmask(a) << '\n';
  cout << getmask(b) << '\n';
  cout << getmask(mergeSums(a,b)) << '\n';
  */
}

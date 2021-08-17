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

const int maxn = 105;
char g[maxn][maxn];

int a, b;
bool isbound(char c) {
  return c == '/' || c == '\\';
}
int inside(int i, int j) {
  if (g[i][j] == '.') {
    bool left = false, right = false, up = false, down = false;
    for (int k = j-1; k >= 0; k--) {
      if (isbound(g[i][k])) left = true;
    }
    for (int k = j+1; k < b; k++) {
      if (isbound(g[i][k])) right = true;
    }
    for (int k = i-1; k >= 0; k--) {
      if (isbound(g[k][j])) up = true;
    }
    for (int k = i+1; k < a; k++) {
      if (isbound(g[k][j])) down = true;
    }
    return left && right && up && down;
  }
  return false;
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int bound = 0, interior = 0;
  cin >> a >> b;
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < b; j++) {
      cin >> g[i][j];
    }
  }
  for (int i = 0; i < a; i++) {
    bool off = true;
    for (int j = 0; j < b; j++) {
      if (isbound(g[i][j])) {
        bound++;
        off = !off;
      }
      else if (g[i][j] == '.' && !off) interior++;
    }
  }
  //cout << "bound = " << bound << '\n';
  //cout << "interior = " << interior << '\n';
  cout << (bound/2+interior) << '\n';
}

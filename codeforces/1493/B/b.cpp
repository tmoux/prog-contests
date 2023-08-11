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

int main() {
  int t; cin >> t;
  map<int,bool> good = {
    {0,1},
    {1,1},
    {2,1},
    {3,0},
    {4,0},
    {5,1},
    {6,0},
    {7,0},
    {8,1},
    {9,0},
  };
  map<int,int> flip = {
    {0,0},
    {1,1},
    {2,5},
    {3,0},
    {4,0},
    {5,2},
    {6,0},
    {7,0},
    {8,8},
    {9,0},
  };

  while (t--) {
    int h, m; cin >> h >> m;
    auto advance = [&](pi& p) {
      p.s++;
      if (p.s == m) {
        p.s = 0;
        p.f++;
      }
      if (p.f == h) {
        p.f = 0;
      }
    };
    auto isvalid = [&](pi p) {
      if (!good[p.f%10] || !good[p.f/10] 
       || !good[p.s%10] || !good[p.s/10]) return false;
      int minutes = flip[p.f/10] + flip[p.f%10]*10;
      int hours   = flip[p.s/10] + flip[p.s%10]*10;
      return hours < h && minutes < m;
    };
    auto convert = [&](string s) {
      return (s[0]-'0')*10+(s[1]-'0');
    };
    string s; cin >> s;
    int H = convert(s.substr(0,2));
    int M = convert(s.substr(3,2));
    pi curr = {H,M};
    while (!isvalid(curr)) {
      advance(curr);
    }
    printf("%02d:%02d\n",curr.f,curr.s);
  }
}

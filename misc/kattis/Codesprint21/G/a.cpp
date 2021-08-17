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

//int A, B;

pair<bool,bool> ask(int l, int r) {
  cout << "ASK" << ' ' << l << ' ' << r << endl;
  //return {l <= A && A <= r, l <= B && B <= r};
  string a, b; cin >> a >> b;
  return {a == "yes", b == "yes"};
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie(NULL);
  //A = 37, B = 497;
  //A = uid(1,500); B = uid(1,500);
  //cout << A << ' ' << B << endl;
  int l1 = 1, r1 = 500, l2 = 1, r2 = 500;
  for (int i = 0; i < 10; i++) {
    //printf("[%d, %d], [%d, %d]\n",l1,r1,l2,r2);
    if (l1 == l2 && r1 == r2) {
      int mid = (l1+r1)/2;
      auto ret = ask(l1,mid);
      if (ret.first) {
        r1 = mid;
      }
      else {
        l1 = mid+1;
      }
      if (ret.second) {
        r2 = mid;
      }
      else {
        l2 = mid+1;
      }
    }
    else {
      bool flip = false;
      int m1, m2;
      if (l1 < l2) {
        m1 = (l1+r1+1)/2;
        m2 = (l2+r2)/2;
      }
      else {
        flip = true;
        m1 = (l2+r2+1)/2;
        m2 = (l1+r1)/2;
      }
      auto ret = ask(m1,m2);
      if (!flip) {
        if (ret.first) l1 = m1;
        else r1 = m1-1;

        if (ret.second) r2 = m2; 
        else l2 = m2+1;
      }
      else {
        if (ret.first) r1 = m2;
        else l1 = m2+1;

        if (ret.second) l2 = m1;
        else r2 = m1-1;
      }
    }
  }
  assert(l1 == r1 && l2 == r2);
  cout << "GUESS " << r1 << ' ' << r2 << endl;
}

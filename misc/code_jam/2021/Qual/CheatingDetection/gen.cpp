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
#define urd(a, b) uniform_real_distribution<double>(a, b)(rng)
 
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

double sigmoid(double x) {
  return 1.0/(1+exp(x));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  cout << T << '\n';
  cout << 86 << '\n';
  while (T--) {
    vector<double> skills(100);
    for (int i = 0; i < 100; i++) skills[i] = urd(-3,3);
    vector<double> diff(10000);
    for (int i = 0; i < 10000; i++) diff[i] = urd(-3,3);
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 10000; j++) {
        double prob = sigmoid(skills[i]-diff[j]);
        double r = urd(0,1);
        if (i == 0) {
          int p = uid(0,1);
          if (p == 0) {
            cout << 1;
          }
          else {
            cout << (r < prob ? '0' : '1');
          }
        }
        else {
          cout << (r < prob ? '0' : '1');
        }
      }
      cout << '\n';
    }
  }
}

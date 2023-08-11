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

struct Fenwick
{
    int n;
    vector<int> bit;
    Fenwick() {}
    Fenwick(int n_) {
        n = n_;
        bit.resize(n+1,0);
    }
    void add(int i, int x) {
        for (; i <= n; i += i & (-i))
            bit[i] += x;
    }

    int sum(int i) {
        int r = 0;
        for (; i; i -= i & (-i)) {
            r += bit[i];
        }
        return r;
    }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  set<int> a[55];
  Fenwick f[55];
  for (int i = 1; i <= 50; i++) {
    f[i] = Fenwick(n+q+5);
  }
  for (int i = n; i >= 1; i--) {
    int ai; cin >> ai;
    a[ai].insert(i);
    f[ai].add(i,1);
  }
  int top = n+1;
  while (q--) {
    int t; cin >> t;
    int mx = *a[t].rbegin();
    int sum = 0;
    //cout << "counts:\n";
    for (int i = 1; i <= 50; i++) {
      //cout << i << ": " << f[i].sum(top)-f[i].sum(mx) << '\n';
      sum += f[i].sum(top)-f[i].sum(mx);
    }
    cout << sum+1 << ' ';
    a[t].erase(mx);
    a[t].insert(top);
    f[t].add(mx,-1);
    f[t].add(top,1);
    top++;
  }
  cout << '\n';
}

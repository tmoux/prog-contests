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

struct Tracker {
  set<int> taken;
  set<int> next;

  void insertNew(int d) {
    assert(!taken.count(d));
    taken.insert(d);
    if (next.count(d)) next.erase(d);
    if (!taken.count(d-1)) {
      next.insert(d-1);
    }
  }

  int findNext(int d) {
    if (!taken.count(d)) {
      insertNew(d);
      return d;
    }
    else {
      auto it = next.upper_bound(d);
      assert (it != next.begin());
      --it;
      int ret = *it;
      insertNew(ret);
      return ret;
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int s, n; cin >> s >> n;

  bool poss = true;
  multiset<int> noneed;
  Tracker t;
  F0R(i, n) {
    int d; cin >> d;
    char c; cin >> c;
    if (c == 'y') {
      int put = t.findNext(d);
      //cout << d << ' ' << put << endl;
      if (put <= 0) poss = false;
    }
    else {
      noneed.insert(d);
    }
  }

  //default value is s
  map<int,int> mp;
  for (int i: t.taken) {
    mp[i] = s-1;
  }
  int curr = 1;
  for (int d: noneed) {
    if (!mp.count(curr)) mp[curr] = s;
    if (mp[curr] == 0) curr++;
    
    if (curr <= d) {
      mp[curr]--;
    }
    else poss = false;
    if (mp[curr] == 0) curr++;
  }

  cout << (poss ? "Yes" : "No") << '\n';

  int BOUND = 2000000;
  set<int> ss;
  for (int i = 0; i < BOUND; i++) {
    ss.insert(i);
  }
}

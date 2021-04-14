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

void solve() {
  int n; cin >> n;
  string s; cin >> s;
  vector<int> same, diff;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') same.push_back(i);
    else diff.push_back(i);
  }
  if (same.size()&1) {
    cout << "NO\n";
    return;
  }
  string v1(n,'#'), v2(n,'#');
  for (int i = 0; i < same.size(); i++) {
    char d = i < same.size()/2 ? '(' : ')';
    v1[same[i]] = v2[same[i]] = d;
  }
  for (int i = 0; i < diff.size(); i++) {
    if (i & 1) {
      v1[diff[i]] = '(';
      v2[diff[i]] = ')';
    }
    else {
      v1[diff[i]] = ')';
      v2[diff[i]] = '(';
    }
  }
  auto check = [](const string& s) {
    int c = 0;
    for (int i = 0; i < s.size(); i++) {
      c += s[i]=='('?1:-1;
      if (c < 0) return false;
    }
    return true;
  };
  if (check(v1) && check(v2)) {
    cout << "YES\n";
    cout << v1 << '\n';
    cout << v2 << '\n';
  }
  else {
    cout << "NO\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}

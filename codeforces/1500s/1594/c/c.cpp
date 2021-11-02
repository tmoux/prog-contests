#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

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
  int n; char c; 
  cin >> n >> c;
  string s; cin >> s;
  if (all_of(all(s), [&](char ch){return ch == c;})) {
    cout << 0 << '\n';
    return;
  }
  else {
    for (int i = 1; i <= n; i++) {
      bool can = true;
      for (int j = i; j <= n; j += i) {
        if (s[j-1] != c) {
          can = false;
          break;
        }
      }
      if (can) {
        cout << 1 << '\n' << i << '\n';
        return;
      }
    }

    cout << 2 << '\n' << n << ' ' << n-1 << '\n';
    return;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}

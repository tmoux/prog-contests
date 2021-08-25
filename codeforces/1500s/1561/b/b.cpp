#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;
 
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

void add(int a, int b, set<int>& s) {
  int bal = min(a, b);
  a -= bal;
  b -= bal;
  int k = a > 0 ? a/2 : (b+1)/2;
  s.insert(k);
  for (int i = 0; i < bal; i++) {
    k += 2;
    s.insert(k);
  }
}

void solve() {
  int a, b; cin >> a >> b;
  set<int> s;
  add(a, b, s);
  add(b, a, s);
  cout << s.size() << '\n';
  for (int k: s) {
    cout << k << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

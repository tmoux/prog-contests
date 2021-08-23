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

void solve() {
  int n; cin >> n;
  vector<int> a(n+1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  if (a[1] == 1) {
    cout << n+1 << ' ';
    for (int j = 1; j <= n; j++) {
      cout << j << ' ';
    }
    cout << '\n';
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (a[i] == 0 && (i == n || a[i+1] == 1)) {
      //1 -> i, n+1, i+1 -> n
      for (int j = 1; j <= i; j++) {
        cout << j << ' ';
      }
      cout << n+1 << ' ';
      for (int j = i+1; j <= n; j++) {
        cout << j << ' ';
      }
      cout << '\n';
      return;
    }
  }
  cout << -1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}

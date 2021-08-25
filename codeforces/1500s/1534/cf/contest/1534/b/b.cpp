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
  vector<int> a(n+2);
  for (int i = 1; i <= n; i++) cin >> a[i];
  ll sum = 0;
  for (int i = 1; i <= n; i++) {
    int take = max(0, min(a[i]-a[i-1], a[i]-a[i+1]));
    a[i] -= take;
    sum += take;
  }
  sum += a[1] + a[n];
  for (int i = 2; i <= n; i++) sum += abs(a[i]-a[i-1]);
  cout << sum << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}

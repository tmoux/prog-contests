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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto& i: a) cin >> i;
    int M = 500;
    ll ans = -1e18;
    for (int i = max(0,n-M); i < n; i++) {
      for (int j = i+1; j < n; j++) {
        ckmax(ans, 1LL*(i+1)*(j+1) - 1LL*k*(a[i]|a[j]));
      }
    }
    cout << ans << '\n';
  }
}

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
  vector<pair<int,int>> v(n); //(power needed, # monsters)
  for (int i = 0; i < n; i++) {
    int k; cin >> k;
    int mx = 0;
    for (int j = 0; j < k; j++) {
      int ai; cin >> ai;
      ckmax(mx, ai-j);
    }
    v[i] = {mx, k};
  }
  sort(all(v));

  auto check = [&v, n](int power) {
    for (auto p: v) {
      int power_needed = p.first;
      int lvlup = p.second;
      if (power <= power_needed) return false;
      power += lvlup;
    }
    return true;
  };
  int lo = 0, hi = 1e9+1;
  while (lo + 1 < hi) {
    int mid = (lo + hi)/2;
    (check(mid) ? hi : lo) = mid;
  }
  cout << hi << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

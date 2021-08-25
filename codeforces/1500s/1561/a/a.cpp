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
    int n; cin >> n;
    vector<int> a(n);
    for (auto& i: a) cin >> i;

    int iter = 0;
    while (1) {
      bool sorted = true;
      for (int i = 0; i+1 < n; i++) {
        if (a[i] > a[i+1]) sorted = false;
      }
      if (sorted) break;

      iter++;
      if (iter % 2 == 1) {
        for (int i = 0; i < n-2; i += 2) {
          if (a[i] > a[i+1]) swap(a[i],a[i+1]);
        }
      }
      else {
        for (int i = 1; i < n-1; i += 2) {
          if (a[i] > a[i+1]) swap(a[i],a[i+1]);
        }
      }
      //cout << a << '\n';
    }
    cout << iter << '\n';
  }
}

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
    int n, m; cin >> n >> m;
    vector<bool> R(2), W(2);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        char c; cin >> c;
        if (c == 'R') R[(i+j)%2] = true;
        else if (c == 'W') W[(i+j)%2] = true;
      }
    }

    if (!R[1] && !W[0]) {
      cout << "YES\n";
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          cout << ((i+j)%2 == 0 ? 'R' : 'W');
        }
        cout << '\n';
      }
    }
    else if (!R[0] && !W[1]) {
      cout << "YES\n";
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          cout << ((i+j)%2 == 0 ? 'W' : 'R');
        }
        cout << '\n';
      }
    }
    else cout << "NO\n";
  }
}

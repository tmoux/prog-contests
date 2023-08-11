#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool solve() {
  int n, U, R, D, L; cin >> n >> U >> R >> D >> L;
  for (int ul: {0,1}) {
    for (int ur: {0,1}) {
      for (int dl: {0,1}) {
        for (int dr: {0,1}) {
          int u = U - (ul + ur);
          int d = D - (dl + dr);
          int r = R - (ur + dr);
          int l = L - (ul + dl);
          if (0 <= u && u <= n-2 &&
              0 <= d && d <= n-2 && 
              0 <= r && r <= n-2 && 
              0 <= l && l <= n-2)
            return true;
        }
      }
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    cout << (solve() ? "YES" : "NO") << '\n';
  }
}

#include <bits/stdc++.h>
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  string s; cin >> s;
  vector<int> pfx(n);
  for (int i = 0; i < n; i++) {
    pfx[i] = (s[i] == '(' ? 1 : -1) + (i == 0 ? 0 : pfx[i-1]);
  }
  if (pfx[n-1] == 0) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (pfx[i] < 0) {
        ans++;
        while (pfx[i] < 0) {
          ans++;
          i++;
        }
      }
    }
    cout << ans << '\n';
  }
  else {
    cout << -1 << '\n';
  }
}

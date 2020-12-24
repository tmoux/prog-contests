#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    string s; cin >> s;
    if (s == "2020") {
      cout << "YES\n";
      goto done;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 1; i+j <= n; j++) {
        if (n-j != 4) continue;
        string t = s.substr(0,i)+s.substr(i+j);
        if (t == "2020") {
          cout << "YES\n";
          goto done;
        }
      }
    }
    cout << "NO\n";
    done:;
  }
}

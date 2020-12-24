#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  int n; cin >> n;
  cout << t << '\n';
  while (t--) {
    for (int i = 0; i < n; i++) {
      if (rand() % 2 == 0) {
        cout << '?';
      }
      else {
        int c = rand() % 26;
        cout << (char)(c+'a');
      }
    }
    cout << '\n';
  }
}


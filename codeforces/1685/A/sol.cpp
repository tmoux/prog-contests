#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n; cin >> n;
  deque<int> a(n);
  for (auto& x: a) cin >> x;
  sort(a.begin(), a.end());
  if (n % 2 == 1) {
    cout << "NO\n";
  }
  else {
    vector<int> b;
    for (int i = 0; i < n/2; i++) {
      b.push_back(a[i]);
      b.push_back(a[i+n/2]);
    }

    bool poss = true;
    for (int i = 0; i < n; i++) {
      int x = i == 0 ? b.back() : b[i-1];
      int y = b[i];
      int z = i+1 == n ? b.front() : b[i+1];
      if ((x < y && y > z) ||
          (x > y && y < z)) {

      }
      else {
        poss = false;
        break;
      }
    }
    if (poss) {
      cout << "YES\n";
      for (auto x: b) {
        cout << x << ' ';
      }
      cout << '\n';
    }
    else {
      cout << "NO\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}


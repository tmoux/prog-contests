#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, m; cin >> n >> m;
    set<int> s;
    for (int i = 0; i < n; i++) {
      int ai; cin >> ai;
      s.insert(ai);
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
      int ai; cin >> ai;
      if (s.count(ai)) ans++;
    }
    cout << ans << '\n';
  }
}


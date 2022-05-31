#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> v;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    v.push_back(x);
  }
  sort(v.begin(), v.end(), greater<int>());
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, v[i-1] + i + 1);
  }
  cout << ans << '\n';
}

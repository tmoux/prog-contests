#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  vector<int> ans(200000);
  ans[0] = 9;
  ans[1] = 8;
  ans[2] = 9;
  for (int i = 3; i < 200000; i++) {
    ans[i] = (ans[i-1]+1) % 10;
  }
  while (t--) {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
      cout << ans[i];
    }
    cout << '\n';
  }
}

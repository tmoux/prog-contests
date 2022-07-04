#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int N; cin >> N;
  vector<int> a(N);
  vector<pair<int, int>> mn(2, {2e9, -1});
  for (int i = 0; i < N; i++) {
    cin >> a[i];
    mn[i%2] = min(mn[i%2], {a[i], i});
  }

  if (N % 2 == 1) {
    cout << "Mike" << '\n';
  }
  else {
    auto [c0, i] = mn[0];
    auto [c1, j] = mn[1];
    if (c0 == c1) {
      cout << (i > j ? "Mike" : "Joe") << '\n';
    }
    else {
      cout << (c0 > c1 ? "Mike" : "Joe") << '\n';
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

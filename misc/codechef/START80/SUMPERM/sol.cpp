#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N; cin >> N;
  if (N&1) {
    cout << -1 << '\n';
  }
  else {
    for (int i = 2; i <= N; i += 2) {
      cout << i << ' ' << i-1 << ' ';
    }
    cout << '\n';
  }
}

int main() {
  int T; cin >> T;
  while (T--) solve();
}

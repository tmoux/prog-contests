#include <bits/stdc++.h>
using namespace std;

bool solve() {
  int N, x, p; cin >> N >> x >> p;
  int target = (N - x) % N;
  for (int f = 1; f <= min(p, 2*N); f++) {
    int ff = (1LL * f * (f + 1) / 2) % N;
    if (ff == target) return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << (solve() ? "YES" : "NO") << '\n';
}

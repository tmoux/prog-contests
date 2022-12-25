#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  int N; cin >> N;
  const int MX = 200000;
  cout << N << '\n';
  for (int q = 0; q < N; q++) {
    int t = rng() % 3 + 1;
    if (t == 1 || t == 2) {
      int x = rng() % MX + 1;
      cout << t << ' ' << x << '\n';
    }
    else {
      cout << t << '\n';
    }
  }
}

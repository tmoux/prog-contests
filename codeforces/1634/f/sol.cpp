#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5+5;
int MOD;
int n, q;

struct ZeroTracker {
  vector<int> a;
  int numZeros;
  ZeroTracker(vector<int> b) {
    a.resize(n);
    for (int i = 0; i < n; i++) {
      a[i] = b[i];
      if (i-1 >= 0) a[i] = (a[i] - b[i-1] + MOD) % MOD;
      if (i-2 >= 0) a[i] = (a[i] - b[i-2] + MOD) % MOD;
    }

    numZeros = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] == 0) numZeros++;
    }
  }

  void add(int i, int x) {
    while (x < 0) x += MOD;
    bool wasZero = a[i] == 0;
    a[i] = (a[i] + x) % MOD;
    bool isZero = a[i] == 0;
    if (wasZero != isZero) {
      if (isZero) numZeros++;
      else if (wasZero) numZeros--;
    }
  }

  bool allZeros() {
    return numZeros == n;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> q >> MOD;
  const int maxn = 3e5+10;
  vector<int> fib(maxn);
  fib[1] = fib[2] = 1;
  for (int i = 3; i < maxn; i++) fib[i] = (fib[i-1] + fib[i-2]) % MOD;

  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    b[i] = (b[i] + MOD - x) % MOD;
  }
  ZeroTracker tracker(b);
  for (int i = 0; i < q; i++) {
    char c; cin >> c;
    int l, r; cin >> l >> r;
    l--; r--;
    int mult = c == 'A' ? 1 : -1;
    tracker.add(l, mult);
    int len = r-l+1;
    if (r+1 < n) tracker.add(r+1, fib[len+1] * -mult);
    if (r+2 < n) tracker.add(r+2, fib[len] * -mult);
    cout << (tracker.allZeros() ? "YES" : "NO") << '\n';
  }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> a(n+1), xo(n+1,0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    xo[i] = a[i];
    xo[i] ^= xo[i-1];
  }
  for (int i = 2; i+1 <= n; i++) {
    if (__builtin_clz(a[i-1]) == __builtin_clz(a[i]) &&
        __builtin_clz(a[i+1]) == __builtin_clz(a[i])) {
      cout << 1 << '\n';
      return 0;
    }
  }
  int ans = n+1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      for (int k = i+1; k <= n; k++) {
        if ((xo[i]^xo[j]) > (xo[k]^xo[i])) {
          ans = min(ans,(i-j-1)+(k-i-1));
        }
      }
    }
  }
  cout << (ans>n?-1:ans) << '\n';
}


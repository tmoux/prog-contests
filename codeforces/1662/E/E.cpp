#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll SZ = 262144;
int* seg = new int[2*SZ];
int combine(int a, int b) {
  return a + b;
}
void update(int p, int value) {
  for (seg[p += SZ] = value; p > 1; p >>= 1)
    seg[p>>1] = combine(seg[(p|1)^1], seg[p|1]);
}
int query(int l, int r) {
  int resL = 0, resR = 0; r++;
  for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
    if (l&1) resL = combine(resL, seg[l++]);
    if (r&1) resR = combine(seg[--r], resR);
  }
  return combine(resL, resR);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int T; cin >> T;
  while (T--) {
    int n; cin >> n;
    for (int i = 0; i <= n; i++) {
      update(i, 0);
    }
    vector<int> p(n+1);
    for (int i = 1; i <= n; i++) {
      int x; cin >> x;
      p[x] = i;
    }

    ll ans = 0;
    int cur = 1;
    for (int i = 1; i <= n; i++) {
      int c;
      if (cur < p[i]) {
        c = query(cur+1, p[i]);
      }
      else {
        c = query(cur+1, n) + query(1, p[i]);
      }
      ans += 1LL * c * (n - i + 1);
      update(p[i], 1);

      cur = p[i];
    }
    cout << ans << '\n';
  }
}

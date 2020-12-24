#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    while (q--) {
      int l, r; cin >> l >> r;
      l--; r--;
      vector<int> fwd(n), bck(n);
      int pt = l;
      for (int i = 0; i < n; i++) {
        if (pt <= r-1 && s[i] == s[pt]) pt++;
        fwd[i] = pt;
      }
      pt = r;
      for (int i = n-1; i >= 0; i--) {
        if (pt >= l+1 && s[i] == s[pt]) pt--;
        bck[i] = pt;
      }
      bool poss = false;
      for (int i = 1; i+1 < n; i++) {
        //cout << i << ": " << fwd[i-1] << ' ' << bck[i+1] << '\n';
        if (fwd[i-1] > bck[i+1]) poss = true;
      }
      cout << (poss?"YES":"NO") << '\n';
    }
  }
}


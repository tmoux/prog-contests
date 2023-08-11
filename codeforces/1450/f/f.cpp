#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> f(n+1,0), ends(n+1,0);
    int cuts = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      f[a[i]]++;
      if (i > 0 && a[i] == a[i-1]) {
        ++ends[a[i]];
        ++ends[a[i-1]];
        cuts++;
      }
    }
    if (*max_element(f.begin(),f.end()) > (n+1)/2) {
      cout << -1 << '\n';
      continue;
    }
    else {
      ends[a[0]]++;
      ends[a[n-1]]++;
      int maxf = *max_element(ends.begin(),ends.end());
      cout << cuts+max(0,maxf-cuts-2) << '\n';
    }
  }
}


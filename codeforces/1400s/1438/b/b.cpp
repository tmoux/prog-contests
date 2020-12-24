#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    set<int> s;
    for (int i = 0; i < n; i++) {
      int bi; cin >> bi;
      s.insert(bi);
    }
    cout << (s.size()==n?"NO":"YES") << '\n';
  }
}

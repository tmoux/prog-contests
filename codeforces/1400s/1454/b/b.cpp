#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    map<int,vector<int>> mp;
    for (int i = 0; i < n; i++) {
      int ai; cin >> ai;
      mp[ai].push_back(i+1);
    }
    for (auto p: mp) {
      if (p.second.size() == 1) {
        cout << p.second[0] << '\n';
        goto done;
      }
    }
    cout << -1 << '\n';
    done:;
  }
}

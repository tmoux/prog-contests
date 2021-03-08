#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int W, P; cin >> W >> P;
  vector<int> a = {0,W};
  for (int i = 0; i < P; i++) {
    int x; cin >> x;
    a.push_back(x);
  }
  sort(a.begin(),a.end());
  set<int> s;
  for (int i = 0; i < a.size(); i++) {
    for (int j = i+1; j < a.size(); j++) {
      s.insert(a[j]-a[i]);
    }
  }
  for (auto i: s) {
    cout << i << ' ';
  }
  cout << '\n';
}

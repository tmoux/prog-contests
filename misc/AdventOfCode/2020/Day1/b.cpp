#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int x;
  vector<int> v;
  while (cin >> x) {
    v.push_back(x);
  }
  int n = v.size();
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      for (int k = j+1; k < n; k++) {
        if (v[i]+v[j]+v[k] == 2020) {
          cout << (v[i]*v[j]*v[k]) << '\n';
          cout << v[i] << ' ' << v[j] << ' ' << v[k] << '\n';
        }
      }
    }
  }
}

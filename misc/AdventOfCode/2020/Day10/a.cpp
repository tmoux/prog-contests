#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  vector<int> v = {0};
  int x;
  while (cin >> x) {
    v.push_back(x);
  }
  sort(v.begin(),v.end());
  v.push_back(v.back()+3);
  int one = 0, three = 0;
  for (int i = 1; i < v.size(); i++) {
    int diff = v[i]-v[i-1];
    if (diff == 1) one++;
    else if (diff == 3) three++;
  }
  for (auto i: v) {
    cout << i << endl;
  }
  cout << one << ' ' << three << '\n';
  cout << one*three << endl;
}

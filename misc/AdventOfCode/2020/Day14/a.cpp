#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string mask;
  map<int,ll> mp;
  string s;
  while (cin >> s) {
    if (s == "mask") {
      string x; cin >> x;
      mask = x;
      reverse(mask.begin(),mask.end());
    }
    else {
      int cell;
      ll val; 
      cin >> cell >> val;
      ll write = 0;
      for (int i = 0; i < mask.size(); i++) {
        if (mask[i] == '0') {

        }
        else if (mask[i] == '1') {
          write |= 1LL<<i;
        }
        else {
          write |= val & (1LL<<i);
        }
      }
      if (mp.count(cell)) {
        cout << "hi " << cell << endl;
      }
      mp[cell] = write;
    }
  }
  ll sum = 0;
  for (auto p: mp) {
    sum += p.second;
  }
  cout << sum << '\n';
}

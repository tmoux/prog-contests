#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string mask;
  map<ll,ll> mp;
  string s;
  while (cin >> s) {
    if (s == "mask") {
      string x; cin >> x;
      mask = x;
      reverse(mask.begin(),mask.end());
    }
    else {
      ll cell;
      ll val; 
      cin >> cell >> val;
      ll loc = 0;
      vector<ll> adds;
      for (int i = 0; i < (int)mask.size(); i++) {
        if (mask[i] == '0') {
          loc |= cell & (1LL<<i);
        }
        else if (mask[i] == '1') {
          loc |= 1LL<<i;
        }
        else {
          adds.push_back(1LL<<i);
        }
      }
      int sz = adds.size();
      for (int i = 0; i < (1<<sz); i++) {
        ll w = loc;
        for (int j = 0; j < sz; j++) {
          if (i&(1<<j)) w += adds[j];
        }
        mp[w] = val;
        cout << "writing " << w << ' ' << val << endl;
      }
    }
  }
  ll sum = 0;
  for (auto p: mp) {
    sum += p.second;
  }
  cout << sum << '\n';
}

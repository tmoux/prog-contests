#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll M = 2089807806;
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  vector<ll> v;
  ll x; 
  while (cin >> x) {
    v.push_back(x);
  }
  for (int i = 0; i < (int)v.size(); i++) {
    ll sum = 0;
    for (int j = i; j < (int)v.size(); j++) {
      sum += v[j];
      if (sum == M) {
        vector<ll> u;
        for (int k = i; k <= j; k++) {
          u.push_back(v[k]);
        }
        sort(u.begin(),u.end());
        cout << u[0]+u.back() << endl;
        return 0;
      }
    }
  }
}


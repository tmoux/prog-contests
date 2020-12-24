#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  cout << fixed << setprecision(12);
  map<string,ld> mp;
  mp["pink"] = 0;
  for (int i = 0; i < n; i++) {
    string O, W;
    ld R;
    cin >> O >> W >> R;
    if (mp.count(W)) {
      if (mp.count(O)) {
        mp[O] = max(mp[O],mp[W]+log(R));
      }
      else {
        mp[O] = mp[W]+log(R);
      }
    }  
  }
  const ld eps = 1e-9;
  if (!mp.count("blue")) {
    cout << 0.0 << '\n';
  }
  else if (mp["blue"] > log(10)-eps) {
    cout << 10.0 << '\n';
  }
  else {
    cout << exp(mp["blue"]) << '\n';
  }
}

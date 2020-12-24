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
  int n = v.size();
  vector<ll> dp(n,0);
  dp[n-1] = 1;
  for (int i = n-2; i >= 0; i--) {
    for (int j = 1; j <= 3; j++) {
      if (i+j < n && v[i]+3 >= v[i+j]) {
        dp[i] += dp[i+j];
      }
    }
  }
  cout << dp[0] << '\n';
}

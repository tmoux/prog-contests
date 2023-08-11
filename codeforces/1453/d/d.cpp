#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve(ll k) {
  //cout << "k = " << k << endl;
  if (k % 2 == 1) {
    cout << -1 << '\n';
    return;
  }
  vector<int> a;
  while (k >= 2) {
    int i = 2;
    while ((1LL<<(i+1))-2 <= k) i++;
    k -= (1LL<<i)-2;
    a.push_back(i-1);
  }
  int sum = accumulate(a.begin(),a.end(),0);
  assert(sum <= 2000);
  cout << sum << '\n';
  for (int i: a) {
    cout << 1 << ' ';
    for (int j = 0; j < i-1; j++) {
      cout << 0 << ' ';
    }
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    ll k; cin >> k;
    solve(k);
  }
}

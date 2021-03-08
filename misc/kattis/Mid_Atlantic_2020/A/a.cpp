#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, k; cin >> n >> k;
  int sum = 0;
  for (int i = 0; i < k; i++) {
    int x; cin >> x;
    sum += x;
  }
  cout << fixed << setprecision(10);
  double mn = (sum+(n-k)*(-3))/(double)n;
  double mx = (sum+(n-k)*(3))/(double)n;
  cout << mn << ' ' << mx << '\n';
}

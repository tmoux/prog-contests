#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a.begin(),a.end(),greater<int>());
  int A = 0, B = 0;
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0) A += a[i];
    else B += a[i];
  }
  cout << A << ' ' << B << '\n';
}


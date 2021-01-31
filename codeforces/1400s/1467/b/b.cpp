#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    auto check = [&n,&a](int i) {
      if (i <= 0 || i >= n-1) return false;
      return (a[i] > a[i-1] && a[i] > a[i+1]) ||
             (a[i] < a[i-1] && a[i] < a[i+1]);
    };
    auto sum = [&check](int i) {
      return check(i-1) + check(i) + check(i+1);
    };
    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans += check(i);
    }
    int sub = 0;
    for (int i = 0; i < n; i++) {
      int tr = 0;
      int orig = sum(i);
      vector<int> v = {a[i]};
      if (i > 0) {
        v.push_back(a[i-1]);
      }
      if (i < n-1) {
        v.push_back(a[i+1]);
      }

      for (int j: v) {
        for (int k = j-1; k <= j+1; k++) {
          int temp = a[i];
          a[i] = k;
          int cnt = sum(i);
          tr = max(tr,orig-cnt);
          a[i] = temp;
        }
      }
      sub = max(sub,tr);
    }
    cout << (ans-sub) << '\n';
  }
}

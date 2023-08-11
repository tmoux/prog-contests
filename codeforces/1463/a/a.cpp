#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int a, b, c; cin >> a >> b >> c;
    int tot = a+b+c;
    if (tot % 9 == 0 && min(a,min(b,c)) >= tot/9) {
      cout << "YES\n";
    }
    else {
      cout << "NO\n";
    }
  }
}


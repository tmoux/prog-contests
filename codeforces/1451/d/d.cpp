#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    ll d, k; cin >> d >> k;
    ll x = 0;
    while (2*(x+k)*(x+k) <= d*d) {
      x += k;
    }
    if (x*x+(x+k)*(x+k) <= d*d) {
      cout << "Ashish" << '\n';
    }
    else {
      cout << "Utkarsh" << '\n';
    }
  }
}

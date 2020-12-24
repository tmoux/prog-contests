#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  if (n % 2 == 1) {
    if (m % 2 == 1) cout << 1 << '\n';
    else {
      cout << (n<m?2:0) << '\n';
    }
  }
  else {
    cout << 0 << '\n';
  }
}


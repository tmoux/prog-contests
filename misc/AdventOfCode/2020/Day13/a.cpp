#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  string s;
  getline(cin,s);
  int minT = 2e9;
  int id = -1;
  while (getline(cin,s)) {
    if (s[0] == 'x') {

    }
    else {
      stringstream ss(s);
      int x; ss >> x;
      for (int i = t; ; i++) {
        if (i % x == 0) {
          if (i < minT) {
            cout << x << ": " << i << '\n';
            minT = i;
            id = x;
          }
          break;
        }
      }
    }
  }
  cout << ((minT-t)*id) << endl;
}

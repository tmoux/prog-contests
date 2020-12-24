#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    string s; cin >> s;
    int a = 0, b = 0;
    int ans = 0;
    for (char c: s) {
      switch (c) {
        case '(': {
                    a++; break;
                  }
        case '[': {
                    b++; break;
                  }
        case ')': {
                    if (a > 0) a--, ans++; break;
                  }
        case ']': {
                    if (b > 0) b--, ans++; break;
                  }
      }
    }
    cout << ans << '\n';
  }
}


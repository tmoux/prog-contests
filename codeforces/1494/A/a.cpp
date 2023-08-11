#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool check(string s) {
  int r = 0;
  for (char c: s) {
    if (c == '(') r++;
    else r--;
    if (r < 0) return false;
  }
  return r == 0;
}

bool solve(string s) {
  for (int i: {0,1}) {
    for (int j: {0,1}) {
      for (int k: {0,1}) {
        string t = s;
        for (char& c: t) {
          if (c == 'A') c = i?'(':')';
          else if (c == 'B') c = j?'(':')';
          else if (c == 'C') c = k?'(':')';
        }
        if (check(t)) return true;
      }
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    string s; cin >> s;
    cout << (solve(s) ? "YES" : "NO") << '\n';
  }
}

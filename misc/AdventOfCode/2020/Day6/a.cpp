#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  set<char> curr;
  for (char c = 'a'; c <= 'z'; c++) curr.insert(c);
  int ans = 0;
  while (getline(cin,s)) {
    if (s == "") {
      ans += curr.size();
      cout << curr.size() << endl;
      for (char c = 'a'; c <= 'z'; c++) curr.insert(c);
    }
    else {
      for (char c = 'a'; c <= 'z'; c++) {
        if (curr.count(c) && s.find(c) == string::npos) {
          curr.erase(c);
        }
      }
    }
  }
  cout << ans << '\n';
}

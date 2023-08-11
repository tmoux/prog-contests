#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    string s; cin >> s;
    sort(s.begin(),s.end());
    cout << s << '\n';
  }
}

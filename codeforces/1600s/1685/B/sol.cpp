#include <bits/stdc++.h>
using namespace std;

bool solve() {
  int a, b, c, d; cin >> a >> b >> c >> d;
  string s; cin >> s;
  int n = s.size();

  int a_cnt = count(s.begin(), s.end(), 'A');
  int b_cnt = count(s.begin(), s.end(), 'B');
  if (!(a_cnt == a + c + d && b_cnt == b + c + d)) return false;

  int extra = 0;
  vector<int> cs, ds;
  for (int i = 0; i+1 < n; i++) {
    if ((i == 0 || s[i] == s[i-1]) && s[i] != s[i+1]) {
      string cur; cur += s[i];
      int j = i;
      while (j+1 < n && s[j] != s[j+1]) {
        j++;
        cur += s[j];
      }
      int sz = cur.size() / 2;
      if (cur.front() == cur.back()) {
        extra += sz;
      }
      else if (cur[0] == 'A') {
        cs.push_back(sz);
      }
      else if (cur[0] == 'B') {
        ds.push_back(sz);
      }
      else assert(false);
      i = j;

      // cout << cur << endl;

      // cout << "c = " << c << endl;
      // cout << "d = " << d << endl;
    }
  }

  sort(cs.begin(), cs.end());
  sort(ds.begin(), ds.end());
  for (int sz: cs) {
    if (sz <= c) {
      c -= sz;
    }
    else extra += sz-1;
  }
  for (int sz: ds) {
    if (sz <= d) {
      d -= sz;
    }
    else extra += sz-1;
  }

  // cout << "extra = " << extra << endl;
  // cout << "c = " << c << endl;
  // cout << "d = " << d << endl;

  // cout << s << endl;
  // assert(c+d <= extra);
  return (c+d <= extra);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    bool b = solve();
    cout << (b ? "YES" : "NO") << '\n';
  }
}


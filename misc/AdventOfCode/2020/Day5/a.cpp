#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  int ans = 0;
  set<int> ss;
  while (getline(cin,s)) {
    string rowS = s.substr(0,7);
    string colS = s.substr(7);
    int row = 0;
    for (int i = 0; i < 7; i++) {
      if (rowS[i] == 'B') row += 1<<(6-i);
    }
    int col = 0;
    for (int i = 0; i < 3; i++) {
      if (colS[i] == 'R') col += 1<<(2-i);
    }
    int id = row * 8 + col;
    cout << row << ' ' << col << ": " << id << '\n';
    ss.insert(id);
    ans = max(ans,id);
  }
  cout << ans << endl;
  for (int i = 1; i <= ans; i++) {
    if (!ss.count(i)) cout << "found " << i << endl;
  }
}

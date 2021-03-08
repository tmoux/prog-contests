#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  vector<pair<int,int>> queens;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      char c; cin >> c;
      if (c == '*') {
        queens.push_back({i,j});
      }
    }
  }
  for (auto i: queens) {
    //cout << i.first << ' ' << i.second << '\n';
  }
  auto check = [](pair<int,int> a, pair<int,int> b) {
    if (a.first == b.first || a.second == b.second) return true;
    int dx = a.first-b.first;
    int dy = a.second-b.second;
    return abs(dx) == abs(dy);
  };
  bool valid = queens.size() == 8;
  for (int i = 0; i < queens.size(); i++) {
    for (int j = i+1; j < queens.size(); j++) {
      if (check(queens[i],queens[j])) {
        valid = false;
        /*
        cout << queens[i].first << ' ' << queens[i].second << '\n';
        cout << queens[j].first << ' ' << queens[j].second << '\n';
        cout << '\n';
        */
      }
    }
  }
  cout << (valid?"valid":"invalid") << '\n';
}

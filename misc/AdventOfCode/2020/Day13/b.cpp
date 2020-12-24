#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  string s;
  getline(cin,s);
  vector<pair<int,int>> v;
  int id = 0;
  while (getline(cin,s)) {
    if (s[0] == 'x') {

    }
    else {
      stringstream ss(s);
      int x; ss >> x;
      v.push_back({x,id});
    }
    id++;
  }
  for (auto i: v) {
    cout << (5*i.first-i.second)%i.first << ' ' << i.first << endl;
  }
  for (int t = 0; ; t++) {
    bool flag = true;
    for (auto i: v) {
      if (t-i.second >= 0 && (t-i.second) % i.first == 0) {

      }
      else {
        flag = false;
        break;
      }
    }
    if (flag) {
      cout << t << endl;
      return 0;
    }
  }
}

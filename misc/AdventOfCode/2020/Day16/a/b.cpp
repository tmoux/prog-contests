#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  vector<pair<int,int>> A(20), B(20);
  int n = 20;
  for (int i = 0; i < n; i++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    A[i] = {a,b};
    B[i] = {c,d};
  }
  vector<int> my(n);
  for (int i = 0; i < n; i++) {
    cin >> my[i];
  }
  string s;
  int tot = 0;
  vector<set<int>> pos(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      pos[i].insert(j);
    }
  }
  while (getline(cin,s)) {
    stringstream ss(s);
    int x;
    bool valid = true;
    vector<set<int>> v(n);
    int idx = 0;
    for (int idx = 0; idx < n; idx++) {
      ss >> x;
      bool poss = false;
      for (int i = 0; i < n; i++) {
        if ((A[i].first <= x && x <= A[i].second) ||
            (B[i].first <= x && x <= B[i].second)) {
          poss = true;
          v[idx].insert(i);
        }
      }
      if (!poss) {
        valid = false;
      }
    }
    if (valid) {
      for (int i = 0; i < n; i++) {
        vector<int> e;
        for (int j: pos[i]) {
          if (!v[i].count(j)) {
            e.push_back(j);
          }
        }
        for (int j: e) pos[i].erase(j);
      }
    }
  }
  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    int idx = -1;
    for (int j = 0; j < n; j++) {
      if ((int)pos[j].size() == 1) {
        idx = *pos[j].begin();
        ans[j] = idx;
      }
    }
    for (int j = 0; j < n; j++) {
      pos[j].erase(idx);
    }
  }
  //for (auto i: ans) cout << i << ' ';
  //cout << '\n';
  ll res = 1;
  for (int i = 0; i < n; i++) {
    if (ans[i] < 6) {
      res *= my[i];
    }
  }
  cout << "res " << res << '\n';
  return 0;
}

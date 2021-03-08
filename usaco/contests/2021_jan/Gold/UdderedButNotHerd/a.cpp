#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int SZ = 26;
vector<int> dp;
int c[SZ][SZ];
int sz = 0;

int f(int mask) {
  int& res = dp[mask];
  if (res != -1) return res;
  vector<int> on, off;
  for (int i = 0; i < sz; i++) {
    if (mask & (1<<i)) on.push_back(i);
    else off.push_back(i);
  }
  if (off.empty()) return res = 0;
  res = 1e9;
  for (int i: off) {
    int add = c[i][i];
    for (int j: on) {
      add += c[i][j];
    }
    res = min(res,add+f(mask|(1<<i)));
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; cin >> s;
  set<char> chars;
  for (char c: s) chars.insert(c);
  map<int,int> mp;
  for (char c: chars) {
    mp[c] = sz++;
  }
  dp.resize(1<<sz,-1);
  for (int i = 0; i + 1 < s.size(); i++) {
    int a = mp[s[i]];
    int b = mp[s[i+1]];
    c[a][b]++;
  }
  /*
  for (int i = 0; i < sz; i++) {
    for (int j = 0; j < sz; j++) {
      cout << c[i][j] << ' ';
    }
    cout << '\n';
  }
  */
  int ans = 1+f(0);
  cout << ans << '\n';
}

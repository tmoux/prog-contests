#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int term(vector<pair<string,int>> v) {
  int acc = 0;
  set<int> seen;
  int cur = 0;
  while (!seen.count(cur)) {
    seen.insert(cur);
    if (cur == (int)v.size()) return acc;
    if (v[cur].first == "nop") {
      cur++;
    }
    else if (v[cur].first == "acc") {
      acc += v[cur].second;
      cur++;
    }
    else {
      cur += v[cur].second; 
    }
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  vector<pair<string,int>> v;
  while (getline(cin,s)) {
    auto c = s.find(' ');
    string a = s.substr(0,c);
    string b = s.substr(c+1);
    stringstream ss(b.substr(1));
    int x; ss >> x;
    if (b[0] == '-') x *= -1;
    cout << a << ' ' << x << '\n';
    v.push_back({a,x});
  }
  for (int i = 0; i < v.size(); i++) {
    if (v[i].first == "nop") {
      v[i].first = "jmp";
      int ret = term(v);
      if (ret != -1) cout << ret << endl;
      v[i].first = "nop";
    }
    if (v[i].first == "jmp") {
      v[i].first = "nop";
      int ret = term(v);
      if (ret != -1) cout << ret << endl;
      v[i].first = "jmp";
    }
  }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void trim(string& s) {
  while (s.back() == ' ') s.pop_back();
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  map<string,vector<string>> mp;
  while (getline(cin,s)) {
    int c = s.find("contain");
    string t1 = s.substr(0,c-6);
    //cout << t1 << endl;
    string t2 = s.substr(c+8);
    if (t2 == "no other bags.") continue;
    t2[t2.size()-1] = ',';
    //cout << t2 << endl;
    trim(t1);
    while ((c = t2.find(",")) != (int)string::npos) {
      string token = t2.substr(0,c-4);
      token = token.substr(2);
      t2.erase(0,c+2);
      trim(token);
      //cout << "token " << token << endl;
      mp[token].push_back(t1);
      cout << t1 << " -> " << token << endl;
      if (token == "shiny gold") {
        //cout << t1 << endl;
      }
    }
  }
  set<string> ans;
  queue<string> q;
  for (auto ss: mp["shiny gold"]) {
    q.push(ss);
    ans.insert(ss);
  }
  while (!q.empty()) {
    string f = q.front(); q.pop();
    for (auto ss: mp[f]) {
      if (!ans.count(ss)) {
        q.push(ss);
        ans.insert(ss);
      }
    }
  }
  cout << ans.size() << endl;
}

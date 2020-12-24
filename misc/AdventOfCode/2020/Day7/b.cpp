#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void trim(string& s) {
  while (s.back() == ' ') s.pop_back();
}

map<string,vector<pair<int,string>>> mp;
map<string,int> deg;
map<string,int> ans;

int calc(string s) {
  int ans = 0;
  for (auto p: mp[s]) {
    int c = p.first;
    string ss = p.second;
    ans += c + c*calc(ss);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
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
      int cnt = token[0]-'0';
      token = token.substr(2);
      t2.erase(0,c+2);
      trim(token);
      //cout << "token " << token << endl;
      mp[t1].push_back({cnt,token});
      deg[t1]++;
      cout << t1 << " -> " << cnt << ' ' << token << endl;
      if (token == "shiny gold") {
        //cout << t1 << endl;
      }
    }
  }
  cout << calc("shiny gold") << '\n';
}

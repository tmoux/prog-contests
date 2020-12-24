#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int read_int(string s) {
  stringstream ss(s);
  int x;
  ss >> x;
  return x;
}

bool check(map<string,string> mp) {
  bool ret = true;
  int byr = read_int(mp["byr"]);  
  ret &= 1920 <= byr && byr <= 2002;

  int iyr = read_int(mp["iyr"]);
  ret &= 2010 <= iyr && iyr <= 2020;

  int eyr = read_int(mp["eyr"]);
  ret &= 2020 <= eyr && eyr <= 2030;

  if ('0' <= mp["hgt"].back() && mp["hgt"].back() <= '9') return false;
  int hgt = read_int(mp["hgt"].substr(0,mp["hgt"].size()-2));
  if (mp["hgt"].back() == 'm')
    ret &= 150 <= hgt && hgt <= 193;
  else 
    ret &= 59 <= hgt && hgt <= 76;

  if (mp["hcl"][0] != '#' || mp["hcl"].size() != 7) return false;

  set<string> eyes = {"amb",
                      "blu",
                      "brn",
                      "gry",
                      "grn",
                      "hzl",
                      "oth",};
  ret &= eyes.count(mp["ecl"]);

  ret &= mp["pid"].size() == 9;
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  map<string,string> mp;
  //ignore cid
  int ans = 0;
  while (getline(cin,s)) {
    if (s == "") {
      if (mp.size() == 7) {
        if (check(mp)) ans++;
      }
      mp.clear();
    }
    else {
      istringstream ss(s);
      string a, val;
      while (getline(ss,a,':')) {
        ss >> val;
        if (a[0] == ' ') a = a.substr(1);
        cout << a << ' ' << val << endl;
        if (a != "cid") mp[a] = val;
      }
    }
  }
  cout << "ans = " << ans << endl;
}

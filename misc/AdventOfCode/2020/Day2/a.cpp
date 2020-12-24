#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int string_to_int(string s) {
  int r = 0;
  int mult = 1;
  for (int i = s.size()-1; i >= 0; i--) {
    r += (s[i]-'0')*mult;
    mult *= 10;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  int ans = 0;
  while (getline(cin,s)) {
    int i = s.find_first_of("-");
    int mn = string_to_int(s.substr(0,i));
    int idx = s.find_first_of(":");
    int mx = string_to_int(s.substr(i+1,idx-3-i));
    char ch = s[idx-1];
    string t = s.substr(idx+2);
    int cnt = (t[mn-1] == ch) + (t[mx-1] == ch);
    if (cnt == 1) ans++;
  }
  cout << ans << '\n';
}

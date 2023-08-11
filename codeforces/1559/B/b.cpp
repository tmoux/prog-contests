#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

void solve() {
  int n; cin >> n;
  string s; cin >> s;
  auto count = [](const string& s) {
    int cnt = 0;
    for (int i = 1; i < s.size(); i++) {
      cnt += s[i-1] == s[i];
    }
    return cnt;
  };
  auto makeString = [](string s) {
    for (int i = 1; i < s.size(); i++) {
      if (s[i] == '?') 
        s[i] = s[i-1] == 'R' ? 'B' : 'R';
    }
    return s;
  };

  string ansString = makeString("R"+s);
  int ans = count(ansString);
  string sb = makeString("B"+s);
  if (ckmin(ans, count(sb))) {
    ansString = sb;
  }
  cout << ansString.substr(1) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

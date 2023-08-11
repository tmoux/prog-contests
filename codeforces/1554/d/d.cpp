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

bool check(const string& s) {
  map<string,int> mp;
  for (int i = 0; i < s.size(); i++) {
    for (int j = 1; i+j <= s.size(); j++) {
      ++mp[s.substr(i,j)];
    }
  }
  for (auto p: mp) if (p.second % 2 == 0) return false;
  return true;
}

string ans;
void genstring(string s, int n) {
  if (!ans.empty()) return;
  if (s.size() == n) {
    if (check(s)) {
      ans = s;
    }
  }
  else {
    for (char c = 'a'; c <= 'c'; c++) {
      genstring(s+c, n);
    }
  }
}

string small_ans[] = {
  "",
  "a",
  "ab",
  "abc"
};

void solve(int n) {
  if (n <= 3) cout << small_ans[n] << '\n';
  else if (n % 2 == 0) {
    for (int i = 0; i < n/2; i++) cout << 'a';
    cout << 'b';
    for (int i = 0; i < n/2-1; i++) cout << 'a';
    cout << '\n';
  }
  else {
    for (int i = 0; i < n/2; i++) cout << 'a';
    cout << 'b';
    for (int i = 0; i < n/2-1; i++) cout << 'a';
    cout << 'c';
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    int n; cin >> n;
    cout << n << ": ";
    solve(n);
  }
}

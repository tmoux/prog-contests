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

int solve() {
  string s; cin >> s;
  auto is_vowel = [](char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
  };

  auto cost = [&](char c) {
    int cost = 0;
    for (char d: s) {
      if (d == c) continue;
      else if (is_vowel(d)^is_vowel(c)) cost++;
      else cost += 2;
    }
    return cost;
  };

  int ans = 2*s.size();
  for (char c = 'A'; c <= 'Z'; c++) {
    ckmin(ans, cost(c));
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}

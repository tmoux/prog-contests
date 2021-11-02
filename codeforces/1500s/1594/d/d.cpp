#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
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
  int n, m; cin >> n >> m;
  vector<vector<int>> same(n), diff(n);
  F0R(_, m) {
    int i, j; string s;
    cin >> i >> j >> s;
    i--; j--;
    if (s == "imposter") {
      diff[i].push_back(j);
      diff[j].push_back(i);
    }
    else {
      same[i].push_back(j);
      same[j].push_back(i);
    }
  }

  vector<int> color(n, -1);

  function<void(int, int, vector<int>&, vector<int>&, bool&)> dfs;
  dfs = [&](int i, int c, vector<int>& zero, vector<int>& one, bool& poss) {
    color[i] = c;
    (c == 0 ? zero : one).push_back(i);
    for (int j: diff[i]) {
      if (color[j] == c) {
        poss = false;
        return;
      }
      else if (color[j] == -1) {
        dfs(j, c^1, zero, one, poss);
      }
    }
    for (int j: same[i]) {
      if (color[j] == (c^1)) {
        poss = false;
        return;
      }
      else if (color[j] == -1) {
        dfs(j, c, zero, one, poss);
      }
    }
  };

  int ans = 0;
  F0R(i, n) {
    if (color[i] == -1) {
      bool poss = true;
      vector<int> zero, one;
      dfs(i, 0, zero, one, poss);

      if (!poss) return -1;
      ans += max(zero.size(), one.size());
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) cout << solve() << '\n';
}

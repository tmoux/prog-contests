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
  int n; cin >> n;
  vector<int> indegree(n, 0);
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) {
    int k; cin >> k;
    indegree[i] = k;
    while (k--) {
      int ai; cin >> ai; ai--;
      adj[ai].push_back(i);
    }
  }
  set<int> canRead;
  F0R(i, n) if (indegree[i] == 0) canRead.insert(i);
  int curPage = 0;
  int ans = 1;
  int numChapters = 0;
  while (!canRead.empty()) {
    if (canRead.lower_bound(curPage) == canRead.end()) {
      //go back to the beginning
      ans++;
      curPage = 0;
    }
    auto it = canRead.lower_bound(curPage);
    assert(it != canRead.end());
    int i = *it;
    curPage = i;
    //cout << "found page " << i+1 << endl;
    canRead.erase(it);
    numChapters++;
    for (int j: adj[i]) {
      if (--indegree[j] == 0) canRead.insert(j);
    }
  }

  if (numChapters < n) return -1;
  else return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}

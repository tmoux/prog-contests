#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
// }}}

class RedGreenBlueLight {
public:
  vector<int> move(vector<int> steps) {
    vector<pair<int,int>> A;
    F0R(i, sz(steps)) {
      A.push_back({steps[i], i});
    }
    sort(all(A));
    int N = sz(A);
    vector<int> ans(N);

    int p = 0;
    vector<int> cur;
    F0R(i, N) {
      ans[A[i].second] = p % 3;
      cur.push_back(A[i].first);
      while (sz(cur) >= 3 && cur[sz(cur)-3] == cur.back()) {
        int v = cur.back();
        cur.pop_back(); cur.pop_back(); cur.pop_back();
        cur.push_back(v-1);
      }
      if (cur[0] == 1) {
        p++;
        cur.clear();
      }
    }
    if (p < 3) return {-1};
    else return ans;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  RedGreenBlueLight t;
  auto ans = t.move({1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << '\n';
}

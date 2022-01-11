#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

class OneBattleship {
public:
  vector<string> hit(vector<string> grid) {
    int N = sz(grid);
    int M = sz(grid[0]);

    vector<vector<pair<int,int>>> v(3);
    F0R(i, N) {
      F0R(j, M) {
        if (grid[i][j] == '.') v[(i+j)%3].push_back({i, j});
      }
    }

    pair<int, vector<pair<int,int>>> ans = {N*M, {}};
    F0R(i, 3) {
      ckmin(ans, {sz(v[i]), v[i]});
    }

    for (auto p: ans.second) {
      int i = p.first;
      int j = p.second;
      grid[i][j] = '*';
    }

    return grid;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
}

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
  int N; cin >> N;
  vector<vector<char>> grid(N, vector<char>(N));
  vector<vector<char>> grid_flipped(N, vector<char>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> grid[i][j];
      grid_flipped[j][i] = grid[i][j];
    }
  }

  const int INF = 1e5;
  auto count_row = [&](int i, const vector<vector<char>>& g) {
    vector<pair<int,int>> cnt;
    for (int j = 0; j < N; j++) {
      if (g[i][j] == 'O') return vector<pair<int,int>>();
      else if (g[i][j] == '.') cnt.push_back({i,j});
    }
    return cnt;
  };

  int minans = INF;
  int mincnt = 0;

  for (int i = 0; i < N; i++) {
    int cnt = count_row(i, grid).size();
    if (cnt > 0 && cnt < minans) {
      minans = cnt;
      mincnt = 1;
    }
    else if (cnt == minans) mincnt++;

    cnt = count_row(i, grid_flipped).size();
    if (cnt > 0 && cnt < minans) {
      minans = cnt;
      mincnt = 1;
    }
    else if (cnt == minans) mincnt++;
  }
  if (minans == INF) {
    cout << "Impossible\n";
  }
  else {
    if (minans > 1) {
      cout << minans << ' ' << mincnt << '\n';
    }
    else {
      set<pair<int,int>> s;
      for (int i = 0; i < N; i++) {
        auto c = count_row(i, grid);
        if (c.size() == 1) for (auto p: c) s.insert(p);
        c = count_row(i, grid_flipped);
        if (c.size() == 1) for (auto p: c) s.insert({p.second,p.first});
      }
      cout << minans << ' ' << s.size() << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": ";
    solve();
  }
}

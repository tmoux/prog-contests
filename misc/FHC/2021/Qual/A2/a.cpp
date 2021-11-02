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

  const int INF = 1e5;
  vector<vector<int>> dist(26, vector<int>(26, INF));

  int K; cin >> K;
  while (K--) {
    char a, b; cin >> a >> b;
    dist[a-'A'][b-'A'] = 1;
  }
  for (int i = 0; i < 26; i++) dist[i][i] = 0;

  for (int k = 0; k < 26; k++) {
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
        ckmin(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  auto cost = [&](char c) {
    int cost = 0;
    for (char d: s) {
      cost += dist[d-'A'][c-'A'];
    }
    return cost;
  };

  int ans = INF;
  for (char c = 'A'; c <= 'Z'; c++) {
    ckmin(ans, cost(c));
  }
  return ans < INF ? ans : -1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<char>> g(n,vector<char>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> g[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && g[i][j] == g[j][i]) {
        // aaaaa... or bbbbb...
        cout << "YES\n";
        for (int k = 0; k < m+1; k++) {
          cout << ((k%2)?i+1:j+1) << ' ';
        }
        cout << '\n';
        return;
      }
    }
  }
  if (m % 2 == 0) {
    // find one node with equal incoming/outgoing edges
    for (int i = 0; i < n; i++) {
      int inA = -1, inB = -1;
      for (int j = 0; j < n; j++) {
        if (g[j][i] == 'a') inA = j;
        if (g[j][i] == 'b') inB = j;
      }
      pair<int,int> found = {-1,-1};
      for (int j = 0; j < n; j++) {
        if (g[i][j] == 'a' && inA != -1) {
          found = {inA,j};
        }
        else if (g[i][j] == 'b' && inB != -1) {
          found = {inB,j};
        }
      }
      if (found != make_pair(-1,-1)) {
        int a = found.first;
        int b = i;
        int c = found.second;
        cout << "YES\n";
        if ((m/2)%2 == 0) {
          cout << b+1 << ' ';
          for (int i = 0; i < m/2; i++) {
            cout << ((i%2)==0?a+1:b+1) << ' ';
          }
          for (int i = 0; i < m/2; i++) {
            cout << ((i%2)==0?c+1:b+1) << ' ';
          }
          cout << '\n';
        }
        else {
          cout << a+1 << ' ';
          for (int i = 0; i < m/2; i++) {
            cout << ((i%2)==0?b+1:a+1) << ' ';
          }
          for (int i = 0; i < m/2; i++) {
            cout << ((i%2)==0?c+1:b+1) << ' ';
          }
          cout << '\n';
        }
        return;
      }
    }
    cout << "NO\n";
  }
  else {
    cout << "YES\n";
    for (int i = 0; i < m+1; i++) {
      cout << ((i%2)?1:2) << ' ';
      cout << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}

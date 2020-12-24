#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void amax(int& a, int b) {
  a = max(a,b);
}
const int maxn = 2005;
void solve() {
  int n; cin >> n;
  vector<vector<int>> a(n,vector<int>(n));
  vector<vector<int>> b(n,vector<int>(n));
  vector<vector<int>> c(n,vector<int>(n));
  vector<vector<int>> d(n,vector<int>(n));

  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < n; j++) {
      a[i][j] = s[j]-'0';
      b[j][n-1-i] = a[i][j];
      c[n-1-i][j] = a[i][j];
      d[n-1-j][i] = a[i][j];
    }
  }
  /*
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << a[i][j];
    }
    cout << '\n';
  }
  */
  auto calc1 = [n](int d, vector<vector<int>>& g) {
    int row = 0;
    for (int i = n-1; i >= 0; i--) {
      for (int j = 0; j < n; j++) {
        if (g[i][j] == d) {
          row = i;
          goto done;
        }
      }
    }
    done: ;
    int res = 0;
    for (int i = 0; i < n; i++) {
      int l = n-1;
      for (int j = 0; j < n; j++) {
        if (g[i][j] == d) {
          l = j; break;
        }
      }
      int r = 0;
      for (int j = n-1; j >= 0; j--) {
        if (g[i][j] == d) {
          r = j; break;
        }
      }
      res = max(res,max(0,r-l)*(n-1-i));
      res = max(res,(n-1-l)*max(0,row-i));
      res = max(res,r*max(0,row-i));
      /*
      if (d == 1) {
        cout << "row = " << row << endl;
        cout << i << ' ' << l << ' ' << r << endl;
      }
      */
    }
    return res;
  };
  for (int digit = 0; digit < 10; digit++) {
    int ans = 0;
    amax(ans,calc1(digit,a));
    amax(ans,calc1(digit,b));
    amax(ans,calc1(digit,c));
    amax(ans,calc1(digit,d));
    cout << ans << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}


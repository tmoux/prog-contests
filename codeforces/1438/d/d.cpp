#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//n even: xor must be 0
//n odd: xor = result elem

const int maxn = 1e5+5;
int n;
int a[maxn];
void output(vector<vector<int>> a) {
  cout << "YES\n";
  cout << a.size() << '\n';
  for (auto v: a) {
    cout << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
  }
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  if (n == 1) {
    cout << "YES\n";
    cout << 0 << '\n';
  }
  else if (n == 2) {
    if (a[0] == a[1]) {
      cout << "YES\n";
      cout << 0 << '\n';
    }
    else {
      cout << "NO\n";
    }
  }
  else if (n == 3) {
    cout << "YES\n";
    cout << "1\n";
    cout << "1 2 3\n";
  }
  else {
    int xo = 0;
    for (int i = 0; i < n; i++) xo ^= a[i];
    if (n % 2 == 0) { //even
      if (xo != 0) {
        cout << "NO\n";
      }
      else {
        vector<vector<int>> ans;
        ans.push_back({1,2,3});
        for (int i = 4; i+2 <= n; i += 2) {
          ans.push_back({i,i+1,i+2});
          ans.push_back({i-1,i,i+1});
        }
        output(ans);
      }
    }
    else { //odd
      vector<vector<int>> ans;
      for (int i = 1; i+2 <= n; i += 2) {
        ans.push_back({i,i+1,i+2});
      }
      for (int i = n-1; i >= 2; i -= 2) {
        ans.push_back({n,i,i-1});
      }
      output(ans);
    }
  }
}


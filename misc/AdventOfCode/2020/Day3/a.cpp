#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N = 323, M = 31;
  vector<string> grid(N);
  for (int i = 0; i < N; i++) {
    cin >> grid[i];
  }
  auto calc = [&grid,N,M](int right, int down) {
    int ret = 0;
    int cur = 0;
    for (int i = 0; i < N; i += down) {
      if (grid[i][cur] == '#') ret++;
      cur = (cur+right) % M;
    }
    return ret;
  };
  int ans = 1;
  ans = ans * calc(1,1);
  ans = ans * calc(3,1);
  ans = ans * calc(5,1);
  ans = ans * calc(7,1);
  ans = ans * calc(1,2);
  cout << ans << '\n';
  cout << calc(1,1) << endl;
  cout << calc(3,1) << endl;
  cout << calc(5,1) << endl;
  cout << calc(7,1) << endl;
  cout << calc(1,2) << endl;
}

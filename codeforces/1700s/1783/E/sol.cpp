#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define F0R(i, a) for (int i = 0; i < (a); i++)
#define sz(x) (int)(x).size()

void solve() {
  int N; cin >> N;
  vector<vector<int>> A(N, vector<int>(2));

  F0R(j, 2) F0R(i, N) cin >> A[i][j];

  vector<int> pfx(N + 2, 0);
  F0R(i, N) {
    if (A[i][0] > A[i][1])
      pfx[A[i][1]]++, pfx[A[i][0]]--;
  }

  for (int i = 1; i <= N; i++) {
    pfx[i] += pfx[i-1];
  }

  vector<int> ans;
  for (int k = 1; k <= N; k++) {
    bool p = true;
    for (int j = k; j <= N; j += k) {
      p &= !pfx[j];
    }
    if (p) ans.push_back(k);
  }

  cout << sz(ans) << '\n';
  F0R(i, sz(ans)) {
    cout << ans[i] << " \n"[i == sz(ans)-1];
  }
}

int main() {
  int T; cin >> T;
  while (T--) solve();
}

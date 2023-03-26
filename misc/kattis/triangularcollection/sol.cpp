#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());
  ll ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      int cnt = 0;
      for (int k = j + 1; k < N; k++) {
        if (A[i] + A[j] > A[k]) cnt++;
        else break;
      }
      ans += (1LL << cnt) - 1;
    }
  }
  cout << ans << '\n';
}

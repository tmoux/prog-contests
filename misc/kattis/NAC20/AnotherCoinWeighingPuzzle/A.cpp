#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int maxn = 1e6+6;
int mu[maxn];

void madd(int& a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
}
int mult(int a, int b) {
  return (1LL * a * b) % MOD;
}

int modexp(int a, int b) {
  int res = 1;
  while (b) {
    if (b&1) res = mult(res, a);
    a = mult(a, a);
    b >>= 1;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int M, K; cin >> M >> K;
  mu[1] = 1;
  for (int i = 1; i < maxn; i++) {
    for (int j = 2*i; j < maxn; j += i) {
      mu[j] -= mu[i];
    }
  }
  int ans = 1;
  for (int d = 1; d <= K; d++) {
    int add = (modexp(2*(K/d)+1, M) - 1 + MOD) % MOD;
    madd(ans, (mu[d] * add + MOD) % MOD);
  }
  cout << ans << '\n';
}

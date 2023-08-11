#include <bits/stdc++.h>
 
using namespace std;

const int maxn = 4e6+5, logn = 23;
int n, MOD;

void madd(int& a, int b) {
  a += b;
  if (a > MOD) a -= MOD;
}
int msub(int a, int b) {
  madd(a, MOD - b);
  return a;
}

int dp[maxn];
int sum[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> MOD;
  dp[1] = 1;
  for (int i = 2; i <= n; i++) {
    madd(sum[i], sum[i-1]);
    madd(sum[i], dp[1]);
    madd(sum[i], dp[i-1]);
    madd(dp[i], sum[i]);

    for (int j = 2*i; j <= n; j += i) {
      madd(sum[j], msub(dp[i], dp[i-1]));
    }
  }
  cout << dp[n] << '\n';
}

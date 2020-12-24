#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

const int maxn = 2e5+5;
int n, dp[maxn];
int a[2];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  dp[n+1] = 1;
  a[(n+1)%2] = 1;
  for (int i = n; i >= 1; i--) {
    dp[i] = a[(i+1)%2];
    madd(a[i%2],dp[i]);
  }
  int ans = mult(dp[1],inverse(modexp(2,n)));
  cout << ans << '\n';
}

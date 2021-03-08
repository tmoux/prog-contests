#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 305;
int N, a[maxn];
int dp[maxn][maxn];

int f(int l, int r) {
  int& res = dp[l][r];
  if (res != -1) return res;
  if (l == r) return res = 1;
  res = 305;
  if (a[l] == a[r]) 
    res = min(f(l+1,r),f(l,r-1));
  for (int k = l; k < r; k++) {
    res = min(res,f(l,k)+f(k+1,r));
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i];
  memset(dp,-1,sizeof dp);
  cout << f(0,N-1) << '\n';
}

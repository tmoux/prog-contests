#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int cnt[10][10];

string s;
int n;
int dp[1<<10];
int f(int mask) {
  int& res = dp[mask];
  if (res != -1) return res;
  for (int i = 0; i < 9; i++) {
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> s;
  n = s.size();
  for (int i = 0; i + 1 < s.size(); i++) {
    int c0 = s[i]-'0';
    int c1 = s[i+1]-'0';
    cnt[min(c0,c1)][max(c0,c1)]++;
  }
  memset(dp,-1,sizeof dp);
}

#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;

const int maxn = 30005;
const int ALPHABET_SIZE = 26;
const int MOD = 998244353;

void madd(int& a, int b) {
  a += b;
  if (a > MOD) a -= MOD;
}
int mult(int a, int b) {
  return (1LL * a * b) % MOD;
}

int N, mid;
string s;
int dp[maxn];

//Returns the corresponding opposite index in the string s.
inline int rev(int i) {
  return N - 1 - i;
}

//count the number of ways two corresponding characters can be matched.
//If two ?, there are ALPHABET_SIZE ways
//If there is one ?, then there is 1 way (match up with the other)
//If they are different characters, there are 0 ways
int count_ways(int i, int j) {
  char a = s[i];
  char b = s[j];
  if (a == '?' && b == '?') return 26;
  else if (a == '?' || b == '?') return 1;
  else return a == b ? 1 : 0;
}

void add_to_dp(int l1, int r1, int l2, int r2, int ways) {
  madd(dp[l1], mult(ways, dp[r1+1]));
  
  if (l1-1 >= 0 && r1+1 < mid) {
    ways = mult(ways, count_ways(l1-1, l2-1));
    ways = mult(ways, count_ways(r1+1, r2+1));
    add_to_dp(l1-1, r1+1, l2-1, r2+1, ways);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> s;
  N = s.size();
  mid = N/2;
  if (N % 2 == 1) dp[mid] = s[mid] == '?' ? ALPHABET_SIZE : 1;
  else dp[mid] = 1;
  for (int i = mid-1; i >= 0; i--) {
    dp[i] = dp[i+1];
    if (s[i] == '?') dp[i] = mult(dp[i], ALPHABET_SIZE);
    if (s[rev(i)] == '?') dp[i] = mult(dp[i], ALPHABET_SIZE);
  }

  for (int i = mid-1; i >= 0; i--) {
    add_to_dp(i, i, rev(i), rev(i), count_ways(i, rev(i)));
    if (i-1 >= 0) {
      int ways = mult(count_ways(i-1, rev(i)), count_ways(i, rev(i-1)));
      add_to_dp(i-1, i, rev(i), rev(i-1), ways);
    }
  }

  cout << dp[0] << '\n';
}

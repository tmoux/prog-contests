#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define sz(x) (int)(x).size()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return b > a ? a = b, 1 : 0;
}

// We can do the following to make a color contiguous:
// (1) Move all to the right.
// (2) Move some prefix of the color to the right, and then move everything in between to the right
// (3) Do nothing and let others in between move.
// Note that we can have at most one type (2) operation.
// Let dp[i] be the max cost of disjoint colors from 1 to i.
// This is the number of indices that don't have to move.
// If we fix some index i as the suffix of a particular color that doesn't move,
// we have dp[i-1] + (# of this color to the right of i) indices that don't move.
// We can compute dp[] in O(n) and then try each index in O(1).

const int maxn = 5e5+5;
int N, A[maxn], L[maxn], cost[maxn], dp[maxn];
vector<int> v[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  FOR(i, 1, N+1) {
    cin >> A[i];
    v[A[i]].push_back(i);
  }

  vector<pair<int, int>> lbs;
  FOR(i, 1, N+1) if (!v[i].empty()) {
    int R = v[i].back();
    L[R] = v[i].front();
    cost[R] = sz(v[i]);

    F0R(j, sz(v[i])) {
      lbs.emplace_back(v[i][j], sz(v[i]) - j);
    }
  }
  FOR(i, 1, N+1) {
    dp[i] = dp[i-1];
    if (L[i]) ckmax(dp[i], dp[L[i]-1] + cost[i]);
  }
  int ans = 1e9;
  for (auto [i, block]: lbs) {
    int tr = N - (block + dp[i-1]);
    ckmin(ans, tr);
  }
  cout << ans << '\n';
}

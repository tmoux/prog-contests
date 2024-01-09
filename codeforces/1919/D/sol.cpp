#include <bits/stdc++.h>
using namespace std;

#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

/*
** Claim: we can make a sequence A iff we can form it by taking a sequence A', selecting a number x in A', and insert x+1 to the left or right of x.
** This motivates trying to reverse this process, starting with the largest elements in A.
** If we find a number x, it must be paired with a number x-1 that is to the left or right, and then we remove it.
** Problem is, what if we have multiple choices? I think it doesn't really matter, as long as we can remove all of a certain distance x at once.
** So, for each x, we should find the nearest left/right element that is smaller than it, and check that at least one of them is x-1.
 */

bool solve() {
  int N; cin >> N;
  vector<int> A(N);
  map<int, vector<int>> mp;
  F0R(i, N) {
    cin >> A[i];
    mp[A[i]].push_back(i);
  }
  set<int> S;
  if (!mp.count(0)) return false;
  for (auto [x, v]: mp) {
    if (x == 0) {
      if (v.size() != 1) return false;
    }
    else {
      for (int i: v) {
        auto it = S.lower_bound(i);
        bool poss = (it != S.begin() && A[*prev(it)] == x-1) ||
          (it != S.end() && A[*it] == x-1);
        if (!poss) {
          return false;
        }
      }
    }
    for (auto i: v) S.insert(i);
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << (solve() ? "YES" : "NO") << '\n';
}

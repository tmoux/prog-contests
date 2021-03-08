#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxx = 2e6+6;
int N;
int a[maxn];
int pre[maxx];

//First, we can transform the problem into
//(a) (floor) dividing all the piles by some positive integer,
//(b) subtracting one from a pile.
//
//One is forced to lose the game if for all x, the number of piles with x stones is even.
//
//So, we need to count, if we are removing k stones, how many piles can force the second player into this position.
//Recall that n/1 + n/2 + n/3 + ... = O(n log(n)).
//use prefix sums

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
    pre[a[i]]++;
  }
  for (int i = 1; i <= 2000000; i++) {
    pre[i] += pre[i-1];
  }
  ll ans = 0;
  for (int k = 1; k <= 1000000; k++) {
    vector<pair<int,int>> odds;
    bool flag = true;
    for (int j = 0; j <= 1000000; j += k) {
      int cnt = pre[j+k-1]-(j?pre[j-1]:0);
      if (j > 0 &&(cnt&1)) 
        odds.push_back({j/k,cnt});
      if (odds.size() > 2) {
        flag = false;
        break;
      }
    }
    if (flag) {
      if (odds.size() == 1) {
        if (odds[0].first == 1) 
          ans += odds[0].second;
      }
      else if (odds.size() == 2) {
        if (odds[0].first+1 == odds[1].first)
          ans += odds[1].second;
      }
    }
  }
  cout << ans << '\n';
}

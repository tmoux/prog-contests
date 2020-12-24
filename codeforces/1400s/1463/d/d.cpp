#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<int> b(2*n+1,0);
    for (int i = 0; i < n; i++) {
      int bi; cin >> bi;
      b[bi] = 1;
    }
    vector<int> x, y;
    for (int i = 1; i <= 2*n; i++) {
      if (b[i]) x.push_back(i);
      else y.push_back(i);
    }
    vector<int> mins(n), maxs(n);
    for (int i = 0; i < n; i++) {
      mins[i] = distance(y.begin(),upper_bound(y.begin(),y.end(),x[i]));
      //cout << i << ": " << mins[i] << endl;
      if (mins[i] != n) {
        mins[i] -= i;
      }
      if (i > 0) mins[i] = max(mins[i],mins[i-1]);
    }
    for (int i = n-1; i >= 0; i--) {
      auto it = lower_bound(y.begin(),y.end(),x[i]);
      if (it == y.begin()) {
        maxs[i] = -1;
      }
      else {
        maxs[i] = distance(y.begin(),prev(it))+(n-1-i);
      }
      if (i < n-1) maxs[i] = min(maxs[i],maxs[i+1]);
    }
    /*
    for (int i = 0; i < n; i++) {
      cout << i << ": " << mins[i] << endl;
    }
    */

    int ans = 0;
    for (int X = 0; X <= n; X++) {
      /*
      if (X-1 >= 0 && X < n) {
        cout << X << ": " << mins[X-1] << ' ' << maxs[X] << '\n';
        cout << (X-1==0 || mins[X-1] <= n-X) << ' ' << (X == n || maxs[X] >= n-X) << '\n';
      }
      */
      if ((X-1< 0 || mins[X-1] <= n-X) &&
          (X == n || maxs[X] >= n-1-X)) {
        ans++;
        //cout << "Ok " << X << endl;
      }
    }
    cout << ans << '\n';
  }
}

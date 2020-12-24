#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    vector<int> x(3,0), y(3,0);
    for (int j = 0; j < 3; j++) {
      x[j] = rand() % 100 + 1;
      y[j] = rand() % 100 + 1;
    }
    int total = accumulate(x.begin(),x.end(),0) + accumulate(y.begin(),y.end(),0);
    int mn = total;
    mn = min(mn,x[0]+y[1]);
    mn = min(mn,x[0]+y[2]);
    mn = min(mn,x[1]+y[0]);
    mn = min(mn,x[1]+y[2]);
    mn = min(mn,x[2]+y[0]);
    mn = min(mn,x[2]+y[1]);

    cout << mn << ' ' << (total/3) << endl;
  }
}


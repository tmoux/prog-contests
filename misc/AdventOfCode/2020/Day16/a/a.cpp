#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  vector<pair<int,int>> A(20), B(20);
  int n = 20;
  for (int i = 0; i < n; i++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    A[i] = {a,b};
    B[i] = {c,d};
  }
  int x; 
  int tot = 0;
  while (cin >> x) {
    bool poss = false;
    for (int i = 0; i < n; i++) {
      if ((A[i].first <= x && x <= A[i].second) ||
          (B[i].first <= x && x <= B[i].second)) {
        poss = true;
        break;
      }
    }
    if (!poss) tot += x;
  }
  cout << tot << '\n';
}

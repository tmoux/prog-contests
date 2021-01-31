#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n[3]; cin >> n[0] >> n[1] >> n[2];
  vector<vector<int>> a(3);
  ll total = 0;
  vector<pair<int,int>> v;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < n[i]; j++) {
      int ai; cin >> ai;
      total += ai;
      a[i].push_back(ai);
      v.push_back({ai,i});
    }
    sort(a[i].begin(),a[i].end());
  }
  sort(v.begin(),v.end()); 
}

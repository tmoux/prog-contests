#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int solve() {
  int n; cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 1; i < n; i++) {
    int p; cin >> p; p--;
    adj[p].push_back(i);
  }
  vector<array<int, 2>> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i][0] >> a[i][1];
  }
  vector<pair<ll, int>> v(n);
  for (int i = n-1; i >= 0; i--) {
    for (int j: adj[i]) {
      v[i].first += v[j].first;
      v[i].second += v[j].second;
    }
    if (v[i].first < a[i][0]) {
      v[i].first = a[i][1];
      v[i].second++;
    }
    else if (v[i].first > a[i][1]) {
      v[i].first = a[i][1];
    }
  }
  return v[0].second;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}

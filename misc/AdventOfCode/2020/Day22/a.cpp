#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n = 25;
  deque<int> p1(n), p2(n);
  for (int i = 0; i < n; i++) {
    cin >> p1[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> p2[i];
  }
  while (!p1.empty() && !p2.empty()) {
    int a = p1.front(); p1.pop_front();
    int b = p2.front(); p2.pop_front();
    if (a > b) {
      p1.push_back(a);
      p1.push_back(b);
    }
    else {
      p2.push_back(b);
      p2.push_back(a);
    }
  }
  if (p1.empty()) swap(p1,p2);
  ll ans = 0;
  for (int i = 0; i < p1.size(); i++) {
    ans += p1[i]*(p1.size()-i);
  }
  cout << ans << '\n';
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  deque<ll> q;
  for (int i = 0; i < 25; i++) {
    int ai; cin >> ai;
    q.push_back(ai);
  }
  ll x;
  while (cin >> x) {
    bool flag = false;
    assert(q.size() == 25);
    for (int i = 0; i < (int)q.size(); i++) {
      for (int j = i+1; j < (int)q.size(); j++) {
        if (q[i]+q[j] == x) {
          flag = true;
          break;
        }
      }
    }
    if (!flag) {
      cout << x << '\n';
      break;
    }
    else {
      cout << x << ' ' << "ok\n";
    }
    q.push_back(x);
    q.pop_front();
  }
}


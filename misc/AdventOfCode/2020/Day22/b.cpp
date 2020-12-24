#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int play(deque<int> p1, deque<int> p2) {
  set<pair<deque<int>,deque<int>>> s;
  int winner = -1;
  while (true) {
    if (p1.empty()) {
      winner = 2; break;
    }
    else if (p2.empty()) {
      winner = 1; break;
    }
    if (s.count({p1,p2})) {
      winner = 1;
      break;
    }
    s.insert({p1,p2});
    int a = p1.front(); p1.pop_front();
    int b = p2.front(); p2.pop_front();
    int w = -1;
    if (a > p1.size() || b > p2.size()) {
      w = a > b ? 1 : 2;
    }
    else {
      deque<int> p1p(p1.begin(),p1.begin()+a);
      deque<int> p2p(p2.begin(),p2.begin()+b);
      w = play(p1p,p2p);
    }
    if (w == 1) {
      p1.push_back(a);
      p1.push_back(b);
    }
    else {
      p2.push_back(b);
      p2.push_back(a);
    }
  }
  auto& v = winner == 1 ? p1 : p2;
  ll ans = 0;
  for (int i = 0; i < v.size(); i++) {
    ans += v[i]*(v.size()-i);
  }
  //cout << "Score " << ans << '\n';
  return winner;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n = 25;
  deque<int> p1(n), p2(n);
  for (auto& i: p1) cin >> i;
  for (auto& i: p2) cin >> i;
  play(p1,p2);
}


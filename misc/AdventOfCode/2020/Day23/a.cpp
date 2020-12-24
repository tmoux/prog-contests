#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  deque<int> a;
  string s; cin >> s;
  for (char c: s) {
    a.push_back((int)(c-'0'));
  }
  int n = a.size();
  for (int iter = 0; iter < 101; iter++) {
    cout << iter << ": ";
    for (auto i: a) {
      cout << i << ' ';
    }
    cout << '\n';
    int cur = a.front();
    int nxt = cur-1;
    if (nxt < 1) nxt = 9;
    while (nxt == a[1] || nxt == a[2] || nxt == a[3]) {
      nxt--;
      if (nxt < 1) nxt = 9;
    }
    //cout << "nxt = " << nxt << '\n';
    assert(nxt != cur && nxt != a[1] && nxt != a[2] && nxt != a[3]);
    int b1 = a[1];
    int b2 = a[2];
    int b3 = a[3];

    int ncur = a[4];

    a.insert(next(find(a.begin(),a.end(),nxt)),b3);
    a.insert(next(find(a.begin(),a.end(),nxt)),b2);
    a.insert(next(find(a.begin(),a.end(),nxt)),b1);

    a.pop_front();
    a.pop_front();
    a.pop_front();
    a.pop_front();


    a.push_back(cur);
    assert(a.front() == ncur);
  }
}

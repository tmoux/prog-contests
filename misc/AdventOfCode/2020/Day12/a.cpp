#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  int x = 0, y = 0;
  int turn = 0;
  while (cin >> s) {
    stringstream ss(s.substr(1));
    int a; ss >> a;
    if (s[0] == 'N') {
      y += a;
    }
    else if (s[0] == 'S') {
      y -= a;
    }
    else if (s[0] == 'E') {
      x += a;
    }
    else if (s[0] == 'W') {
      x -= a;
    }
    else if (s[0] == 'L') {
      a /= 90;
      turn = (turn+a)%4;
    }
    else if (s[0] == 'R') {
      a /= 90;
      turn = (turn-a+4)%4;
    }
    else if (s[0] == 'F') {
      if (turn == 0) {
        x += a;
      }
      else if (turn == 1) {
        y += a;
      }
      else if (turn == 2) {
        x -= a;
      }
      else if (turn == 3) {
        y -= a;
      }
    }
  }
  cout << abs(x) + abs(y) << endl;
}

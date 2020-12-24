#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  int x = 0, y = 0;
  int wx = 10, wy = 1;
  int turn = 0;
  while (cin >> s) {
    stringstream ss(s.substr(1));
    int a; ss >> a;
    if (s[0] == 'N') {
      wy += a;
    }
    else if (s[0] == 'S') {
      wy -= a;
    }
    else if (s[0] == 'E') {
      wx += a;
    }
    else if (s[0] == 'W') {
      wx -= a;
    }
    else if (s[0] == 'L') {
      if (a == 90) {
        int temp = wx;
        wx = -wy;
        wy = temp;
      }
      else if (a == 180) {
        wx *= -1;
        wy *= -1;
      }
      else if (a == 270) {
        int temp = wx;
        wx = wy;
        wy = -temp;
      }
    }
    else if (s[0] == 'R') {
      if (a == 90) {
        int temp = wx;
        wx = wy;
        wy = -temp;
      }
      else if (a == 180) {
        wx *= -1;
        wy *= -1;
      }
      else if (a == 270) {
        int temp = wx;
        wx = -wy;
        wy = temp;
      }
    }
    else if (s[0] == 'F') {
      x += a*wx;
      y += a*wy;
    }
  }
  cout << abs(x) + abs(y) << endl;
}

#include <bits/stdc++.h>
using namespace std;

int n;

int ask(int p) {
  ++p;
  int a, b;
  cout << "? " << p << endl;
  cin >> a;
  cout << "? " << p + n / 2 << endl;
  cin >> b;
  if (a == b) {
    cout << "! " << p << endl;
    exit(0);
  }
  return a < b;
}

int main() {
  cin >> n;
  int type = ask(0), l = 0, r = n / 2;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (ask(m) == type) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << "! -1" << endl;
}

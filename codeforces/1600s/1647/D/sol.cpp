#include <bits/stdc++.h>
using namespace std;

bool isprime(int x) {
  for (int i = 2; i*i <= x; i++) {
    if (x % i == 0) return false;
  }
  return true;
}

bool solve() {
  int x, d; cin >> x >> d;
  int n = 0;
  while (x % d == 0) {
    x /= d;
    n++;
  }
  int y = x;
  if (n == 1) return false;
  else if (y > 1 && !isprime(y)) return true;
  else if (isprime(d) || n == 2 ||
          (d % y == 0 && isprime(d/y) && d/(d/y) == d/y && n == 3)) 
    return false;
  else return true;
}

int main() {
  int T; cin >> T;
  while (T--) cout << (solve() ? "YES" : "NO") << '\n';
}

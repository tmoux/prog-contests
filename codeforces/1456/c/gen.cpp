#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, k; cin >> n >> k;
  random_device device;
  mt19937 gen(device());
  cout << n << ' ' << k << '\n';
  for (int i = 0; i < n; i++) {
    cout << ((rand() % 2000000)-1000000) << ' ';
  }
  cout << '\n';
}


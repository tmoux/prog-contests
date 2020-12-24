#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    string s; cin >> s;
    int n = s.size();
    int glob = 0;
    for (char c: s) {
      glob ^= (1<<(c-'a'));
    }
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        int mask = 0;
        int par = 0;
        for (int k = i; k <= j; k++) {
          if (s[i] == '?') par ^= 1;
          else mask ^= 1<<:wq

        }
      }
    }
  }
}

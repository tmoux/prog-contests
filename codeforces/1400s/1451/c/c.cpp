#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, k; cin >> n >> k;
    string a, b; cin >> a >> b;
    map<char,int> ma, mb;
    for (char c: a) ++ma[c];
    for (char c: b) ++mb[c];
    bool poss = true;
    for (char c = 'a'; c <= 'z'; c++) {
      if (mb[c] > ma[c]) {
        poss = false;
        break;
      }
      else if ((ma[c]-mb[c]) % k != 0) {
        poss = false;
        break;
      }
      else {
        ma[c+1] += ma[c]-mb[c];
      }
    }
    cout << (poss?"Yes":"No") << '\n';
  }
}


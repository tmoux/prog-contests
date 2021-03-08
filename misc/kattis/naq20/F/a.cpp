#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  string s;
  string simon = "Simon says";
  while(getline(cin,s)) {
    if (s.substr(0,simon.size()) == simon) {
      cout << s.substr(simon.size()) << '\n';
    }
  }
}

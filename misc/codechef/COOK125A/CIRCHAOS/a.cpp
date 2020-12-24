#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<int,int>> v;
int X = 1;
void rec(int i, int num, int n) {
  if (i == (int)v.size()) {
    //cout << "trying " << num << '\n';
    if (num <= n) {
      X = max(X,num);
    }
    return;
  }
  int mult = 1;
  for (int j = 0; j <= v[i].second; j++) {
    rec(i+1,num*mult,n);
    mult *= v[i].first;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, m; cin >> n >> m;
    vector<int> p(m);
    int gc = 0;
    for (int i = 0; i < m; i++) {
      cin >> p[i];
      gc = __gcd(gc,p[i]);
    }
    int cp = gc;
    map<int,int> mp;
    for (int i = 2; i*i <= gc; i++) {
      while (cp % i == 0) {
        mp[i]++;
        cp /= i;
      }
    }
    if (cp > 1) mp[cp]++;

    v.clear();
    for (auto i: mp) {
      v.push_back(i);
      //cout << gc << ": " << i.first << ' ' << i.second << '\n';
    }
    X = 1;
    rec(0,1,n);
    //cout << "ans " << gc << ": " << n-X << '\n';
    cout << n-X << '\n';
  }
}

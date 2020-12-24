#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

int n;
string s;
int glob;
ll ans = 0;

void f(int l, int r) {
  if (l == r) {
    if (s[l] == '?') {
      if (__builtin_popcount(glob) == 1) ans++;
    }
    else {
      int mask = 1<<(s[l]-'a');
      if (glob == mask) ans++;
    }
    return;
  }
  int m = (l+r)/2;
  f(l,m);
  f(m+1,r);

  gp_hash_table<int,int> mp[2];
  mp[0].clear(); mp[1].clear();
  int mask = glob;
  int par = 0;
  for (int i = m; i >= l; i--) {
    if (s[i] == '?') {
      par ^= 1;
    }
    else {
      mask ^= (1<<(s[i]-'a'));
    }
    mp[par][mask]++;
  }

  mask = 0;
  par = 0;
  for (int i = m+1; i <= r; i++) {
    if (s[i] == '?') {
      par ^= 1;
    }
    else {
      mask ^= (1<<(s[i]-'a'));
    }

    if (mp[par].find(mask) != mp[par].end()) {
      ans += mp[par][mask];
    }
    for (int j = 0; j < 26; j++) {
      if (mp[par^1].find(mask^(1<<j)) != mp[par^1].end()) {
        ans += mp[par^1][mask^(1<<j)];
      }
    }
  }
}

void solve() {
  cin >> s;
  n = s.size();
  glob = 0;
  vector<int> cnt(26,0);
  for (char c: s) if (c != '?') {
    glob ^= (1<<(c-'a'));
  }
  ans = 0;
  f(0,n-1);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}

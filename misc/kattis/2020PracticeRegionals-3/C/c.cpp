#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n;
ll a[maxn];

void uniques(vector<ll>& v) {
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
}

vector<ll> ans;
void f(int l, int r) {
  if (l == r) {
    ans.push_back(a[l]);
    return;
  }
  int m = (l+r)/2;
  vector<ll> ls = {a[m]}; ls.reserve(60);
  for (int i = m; i >= l; i--) {
    ll gc = __gcd(a[i],ls.back());
    if (gc != ls.back()) ls.push_back(gc);
  }
  vector<ll> rs = {a[m+1]}; rs.reserve(60);
  for (int i = m+1; i <= r; i++) {
    ll gc = __gcd(a[i],rs.back());
    if (gc != rs.back()) rs.push_back(gc);
  }
  vector<ll> vs;
  for (auto i: ls) {
    for (auto j: rs) {
      vs.push_back(__gcd(i,j));
    }
  }
  uniques(vs);
  for (auto i: vs) ans.push_back(i);

  f(l,m);
  f(m+1,r);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  f(0,n-1);
  uniques(ans);
  cout << ans.size() << '\n';
}

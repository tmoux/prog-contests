#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q, a[maxn];
ll pre[maxn];
vector<ll> sums;

void f(int l, int r) {
  sums.push_back(pre[r]-(l==0?0LL:pre[l-1]));
  int mid = (a[l]+a[r])/2;
  auto lb = upper_bound(a,a+n,mid);
  int d = lb-a;
  if (d-1 < r) {
    f(l,d-1);
    f(d,r);
  }
}
void solve() {
  cin >> n >> q;  
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a,a+n);
  for (int i = 0; i < n; i++) {
    pre[i] = a[i];
    if (i > 0) pre[i] += pre[i-1];
  }
  sums.clear();
  f(0,n-1);
  sort(sums.begin(),sums.end());

  while (q--) {
    ll s; cin >> s;
    auto it = lower_bound(sums.begin(),sums.end(),s);
    if (it != sums.end() && *it == s) {
      cout << "Yes\n";
    }
    else {
      cout << "No\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}

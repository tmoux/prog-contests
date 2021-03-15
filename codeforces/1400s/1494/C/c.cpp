#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) begin(x),end(x)
#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

bool in_vec(vector<int>& v, int x) {
  auto it = lower_bound(all(v),x);
  return it != v.end() && *it == x;
}

int calc(vector<int> a, vector<int> b) {
  int ans = 0;
  int cur = 0;
  DEBUG(a);
  for (auto i: a) if (in_vec(b,i)) cur++;
  for (int x: b) {
    if (in_vec(a,x)) cur--;
    auto it = upper_bound(all(a),x);
    int cnt = distance(a.begin(),it);

    it = upper_bound(all(b),x-cnt);
    auto it2 = upper_bound(all(b),x);
    ans = max(ans,cur+(int)distance(it,it2));
  }
  //cout << "ans = " << ans << '\n';
  return ans;
}

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> a(2,vector<int>());
  vector<vector<int>> b(2,vector<int>());
  for (int i = 0; i < n; i++) {
    int ai; cin >> ai;
    if (ai > 0) a[0].push_back(ai);
    else a[1].push_back(-ai);
  }
  for (int i = 0; i < m; i++) {
    int bi; cin >> bi;
    if (bi > 0) b[0].push_back(bi);
    else b[1].push_back(-bi);
  }
  int ans = 0;
  sort(all(a[0]));
  sort(all(b[0]));
  sort(all(a[1]));
  sort(all(b[1]));
  ans += calc(a[0],b[0]);
  ans += calc(a[1],b[1]);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}

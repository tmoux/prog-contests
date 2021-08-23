#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

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

const int maxn = 1e5+5;

struct DSU {
  int sz;
  vector<int> par;

  DSU(int _n) {
    sz = _n;
    par = vector<int>(sz, -1);
  }

  bool same_component(int i, int j) {
    return find_root(i) == find_root(j);
  }

  //Find the root of the component containing i, applying path compression
  int find_root(int i) {
    return par[i] < 0 ? i : par[i] = find_root(par[i]);
  }

  //Returns true if a and b were in different components
  bool merge(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b) return false; 
    if (-par[a] < -par[b]) swap(a,b);
    par[a] += par[b];
    par[b] = a;
    return true;
  }
};

int n, m1, m2;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m1 >> m2;
  DSU f1(n), f2(n);
  for (int i = 0; i < m1; i++) {
    int a, b; cin >> a >> b; a--, b--;
    f1.merge(a,b);
  }
  for (int i = 0; i < m2; i++) {
    int a, b; cin >> a >> b; a--, b--;
    f2.merge(a,b);
  }

  vector<pair<int,int>> ans;
  for (int i = 1; i < n; i++) {
    if (!f1.same_component(0, i) && !f2.same_component(0, i)) {
      f1.merge(0, i);
      f2.merge(0, i);
      ans.push_back({0,i});
    }
  }

  int p1 = 0, p2 = 0;
  while (p1 < n && p2 < n) {
    if (f1.same_component(0, p1)) p1++;
    else if (f2.same_component(0, p2)) p2++;
    else {
      assert(!f1.same_component(p1, p2));
      assert(!f2.same_component(p1, p2));
      f1.merge(p1, p2);
      f2.merge(p1, p2);
      ans.push_back({p1, p2});
      p1++, p2++;
    }
  }

  //output
  cout << ans.size() << '\n';
  for (auto e: ans) {
    cout << e.first+1 << ' ' << e.second+1 << '\n';
  }
}

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

bool solve() {
  int n; cin >> n;
  n = 1<<n;
  map<int, vector<pair<int,int>>> mp;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x; cin >> x;
      mp[x].push_back({i,j});
    }
  }

  auto is_triomino = [](pair<int,int> a, pair<int,int> b, pair<int,int> c) {
    int max_x = max(a.first,max(b.first,c.first));
    int min_x = min(a.first,min(b.first,c.first));

    int max_y = max(a.second,max(b.second,c.second));
    int min_y = min(a.second,min(b.second,c.second));

    return max_x - min_x == 1 && max_y - min_y == 1;
  };

  for (auto& p: mp) {
    int color = p.first;
    auto& v = p.second;

    if (color == 0) {
      if (v.size() != 1) return false;
    }
    else {
      if (v.size() != 3) return false;
      if (!is_triomino(v[0],v[1],v[2])) return false;
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cout << solve() << '\n';
}

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

const int maxn = 2005;
int n;
int par[maxn];
vector<int> ask(int i) {
  cout << "? " << i << endl;
  vector<int> v(n+1);
  for (int j = 1; j <= n; j++) cin >> v[j];
  return v;
}

void add_parent(int i, int p) {
  //cout << "adding " << i << ' ' << p << endl;
  par[i] = p;
}

void solve(int root, vector<int> dist) {
  map<int,vector<int>> dists;
  dists[root] = dist;
  for (int i = 1; i <= n; i++) {
    if (i != root && dist[i] % 2 == 0) {
      dists[i] = ask(i);
    }
  }
  /*
  for (auto d: dists) {
    cout << d.first << ": ";
    for (int i = 1; i <= n; i++) {
      cout << d.second[i] << ' ';
    }
    cout << '\n';
  }
  */
  map<int,vector<int>> mp;
  for (int i = 1; i <= n; i++) {
    mp[dists[root][i]].push_back(i);
  }
  int max_depth = mp.rbegin()->first;
  set<int> parents = {root};
  for (int d = 1; d <= max_depth; d++) {
    /*
    cout << "depth " << d << endl;
    for (int i: parents) {
      cout << i << ' ';
    }
    cout << endl;
    */
    set<int> new_parents;
    if (d % 2 == 1) {
      for (int p: parents) {
        for (int i: mp[d]) {
          if (dists[p][i] == 1) {
            add_parent(i, p);
            new_parents.insert(i);
          }
        }
      }
    }
    else {
      for (int i: mp[d]) {
        for (int p: parents) {
          if (dists[i][p] == 1) {
            add_parent(i, p);
            new_parents.insert(i);
          }
        }
      }
    }
    parents = new_parents;
  }
  //output
  cout << '!' << endl;
  for (int i = 1; i <= n; i++) {
    if (i != root) cout << i << ' ' << par[i] << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  auto dist1 = ask(1);
  vector<int> evens, odds;
  map<int,vector<int>> mp;
  for (int i = 1; i <= n; i++) {
    (dist1[i] % 2 == 0 ? evens : odds).push_back(i);
    mp[dist1[i]].push_back(i);
  }
  if (evens.size() <= odds.size()) {
    solve(1, dist1);
  }
  else {
    int new_root = mp[1][0];
    solve(new_root, ask(new_root));
  }
}

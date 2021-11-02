#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
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

int solve() {
  int N, M; cin >> N >> M;  
  vector<int> style(M);
  map<int,vector<bool>> models; //has used free change?
  for (int i = 0; i < M; i++) {
    cin >> style[i];
    models[style[i]].push_back(false);
  }

  int ans = 0;
  vector<int> p(M);
  for (int round = 0; round < N; round++) {
    for (int i = 0; i < M; i++) cin >> p[i];
    for (auto& p: models) {
      sort(all(p.second));
    }

    map<int,vector<bool>> new_models;
    vector<int> changes;
    for (int i = 0; i < M; i++) {
      int s = p[i];
      if (models.count(s)) {
        new_models[s].push_back(models[s].back());
        models[s].pop_back();
        if (models[s].empty()) models.erase(s);
      }
      else {
        changes.push_back(s);
      }
    }
    vector<bool> models_left;
    for (auto& p: models) {
      for (bool b: p.second) {
        models_left.push_back(b);
      }
    }
    //sort(all(models_left)); reverse(all(models_left));
    for (int s: changes) {
      assert(!models_left.empty());
      int b = models_left.back();
      models_left.pop_back();
      if (!b) {
        new_models[s].push_back(true);
      }
      else {
        new_models[s].push_back(true);
        ans++;
      }
    }
    models = new_models;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}

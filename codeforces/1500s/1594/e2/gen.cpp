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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cout << 60 << '\n';
  cout << 2000 << '\n';

  random_device device;
  mt19937 gen(device());
  uniform_int_distribution<ll> dist(1,(1LL<<60)-1);
  uniform_int_distribution<int> color_dist(0, 5);

  string color[] = {
    "white",
    "yellow",
    "green",
    "blue",
    "red",
    "orange",
  };

  F0R(i, 2000) {
    ll v = dist(gen);
    int s = color_dist(gen);
    cout << v << ' ' << color[s] << '\n';
  }
}

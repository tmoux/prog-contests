#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

namespace std {
  template<class Fun>
    class y_combinator_result {
      Fun fun_;
      public:
      template<class T>
        explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

      template<class ...Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template<class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
} // namespace std

// }}}

void solve() {
  int N; cin >> N;
  const int SZ = 1000;
  vector<bitset<SZ>> adj(N);
  F0R(i, N) {
    string s; cin >> s;
    F0R(j, N) {
      adj[i][j] = s[j] == '1';
    }
  }

  int half = N/2;
  int num_left = half;
  int num_right = N-1-half;

  auto top_sort = [&](vector<int> v) -> vector<int> {
    bitset<SZ> in;
    for (int i: v) in[i] = true;
    vector<pair<int,int>> vec;
    for (int i: v) {
      int wins = (adj[i]&in).count();
      vec.push_back({wins, i});
    }
    sort(all(vec), greater<pair<int,int>>());
    for (int i = 0; i+1 < sz(vec); i++) {
      if (vec[i].first == vec[i+1].first) {
        return {-1};
      }
    }
    
    vector<int> order;
    for (int i = 0; i < sz(vec); i++) {
      order.push_back(vec[i].second);
    }
    return order;
  };

  F0R(i, N) {
    vector<int> beats_i, beaten_by_i;
    F0R(j, N) if (j != i) {
      if (adj[i][j]) beaten_by_i.push_back(j);
      else beats_i.push_back(j);
    }

    //cout << sz(beats_i) << ' ' << sz(beaten_by_i) << endl;
    //cout << num_left << ' ' << num_right << endl;
    if (sz(beats_i) == num_left && sz(beaten_by_i) == num_right) {

      auto left_order = top_sort(beats_i);
      auto right_order = top_sort(beaten_by_i);

      if ((!left_order.empty() && left_order[0] == -1) 
       || (!right_order.empty() && right_order[0] == -1)) continue;

      vector<int> a;
      for (int j: left_order) a.push_back(j);
      a.push_back(i);
      for (int j: right_order) a.push_back(j);

      /*
      cout << "trying " << i << endl;
      for (int j: a) cout << j+1 << ' ';
      cout << '\n';
      */

      //check if valid
      bool valid = true;

      int split = (N+1)/2;
      bitset<SZ> shouldBeat;
      for (int j = 0; j < split; j++) {
        shouldBeat[a[j]] = 1;
      }
      for (int j = 0; j < N; j++) {
        if (j + split < N) shouldBeat[a[j+split]] = 1;
        shouldBeat[a[j]] = 0;

        /*
        cout << "j = " << j << endl;
        cout << (adj[a[j]] & shouldBeat) << endl;
        cout << shouldBeat << endl;
        */

        if ((adj[a[j]] & shouldBeat) == shouldBeat) {

        }
        else {
          valid = false;
          break;
        }
      }
      /*
      cout << "TESTING" << endl;
      for (int j: a) {
        cout << j+1 << ' ';
      }
      cout << '\n';
      */

      if (valid) {
        //cout << "FOUND" << endl;
        //output
        for (int j: a) {
          cout << j+1 << ' ';
        }
        cout << '\n';
        return;
      }
    }
  }
  cout << -1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}

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

template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) 
  requires Container<U<T>> && (!requires(std::ostream o, T a) { operator<<(o, a); })
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

int solve(
    int n, 
    const vector<vector<int>>& w1, 
    const vector<vector<int>>& w2,
    const vector<int>& sum,
    map<pair<int,int>, bool>& direction) 
{
  vector<int> num_flips(n, 0);

  auto get_direction = [&](int u, int v) -> bool {
    // is u -> v ?
    bool parity = (num_flips[u] + num_flips[v]) & 1;
    if (direction.count({u, v})) {
      return parity ^ direction[{u, v}];
    }
    else if (direction.count({v, u})) {
      return !(parity ^ direction[{v, u}]);
    }
    else assert(false);
  };

  auto flip_vertex = [&](int v) -> void {
    num_flips[v]++;
  };

  auto direct_out = [&](int u, int v) -> void {
    if (!get_direction(u, v)) {
      flip_vertex(v);
    }
  };

  auto direct_in = [&](int u, int v) -> void {
    if (get_direction(u, v)) {
      flip_vertex(v);
    }
  };

  int answer = 0;
  F0R(i, n) {
    // Initially direct all edges (i < j), i -> j
    // if i has odd sum:
    // flip edges to get proper sum
    // For each edge: 
    //   - check orientation
    //   - If needs to be flipped, "flip" adjacent vectex
    if (sum[i] % 2 == 1) {
      int total = 0;
      for (int j: w2[i]) {
        if (total == 0) {
          direct_out(i, j);
          total += 2;
        }
        else {
          direct_in(i, j);
          total -= 2;
        }
      }

      for (int j: w1[i]) {
        if (total == 0) {
          direct_out(i, j);
          total++;
        }
        else if (total == 2) {
          direct_in(i, j);
          total--;
        }
        else if (total == 1) {
          direct_in(i, j);
          total--;
        }
        else assert(false);
      }

      assert(total == 1);
      answer++;
    }
  }

  for (auto& [p, b] : direction) {
    b = get_direction(p.first, p.second);
  }
  return answer;
}

struct Edge {
  int id, weight;
  bool flipped;
};
struct MultiEdge {
  vector<int> ids;
  map<int, bool> isFlipped;
  map<int, bool> direction;
  int weight;

  MultiEdge() {}
  MultiEdge(vector<Edge> edges) {
    vector<int> w1, w2;
    for (auto& e: edges) {
      ids.push_back(e.id);
      isFlipped[e.id] = e.flipped;

      if (e.weight == 1) w1.push_back(e.id);
      else if (e.weight == 2) w2.push_back(e.id);
      else assert(false);
    }


    weight = 0;
    for (int i: w2) {
      if (weight == 0) {
        direction[i] = false;
        weight += 2;
      }
      else {
        direction[i] = true;
        weight -= 2;
      }
    }
    for (int i: w1) {
      if (weight == 0) {
        direction[i] = false;
        weight++;
      }
      else if (weight == 2) {
        direction[i] = true;
        weight--;
      }
      else if (weight == 1) {
        direction[i] = true;
        weight--;
      }
      else assert(false);
    }

    assert(weight == 0 || weight == 1 || weight == 2);
    /*
    if (sz(edges) > 1) {
      cout << "HUH\n";
      cout << w1 << ' ' << w2 << endl;
      DEBUG(weight);
    }
    */
  }

  map<int, bool> uncompress(bool dir) {
    map<int, bool> ret;
    for (int i: ids) {
      ret[i] = dir ^ direction[i] ^ isFlipped[i];
    }
    return ret;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  vector<int> sum(n);
  map<pair<int,int>, vector<Edge>> edges;
  map<int, int> weights;
  F0R(i, m) {
    int u, v, w; cin >> u >> v >> w;
    u--; v--;

    weights[i] = w;

    bool flipped = false;
    if (u > v) {
      swap(u, v);
      flipped = true;
    }
    
    edges[{u, v}].push_back({i, w, flipped});

    sum[u] += w;
    sum[v] += w;
  }

  // Condense multiple edges into a single/no edge.
  
  vector<vector<int>> w1(n), w2(n);
  map<pair<int,int>, bool> direction;

  map<pair<int,int>, MultiEdge> multi_edges;
  for (auto& [p, vec]: edges) {
    MultiEdge me(vec);
    multi_edges[p] = me;
    direction[p] = false;

    auto [u, v] = p;
    if (me.weight == 1) {
      w1[u].push_back(v);
      w1[v].push_back(u);
    }
    else if (me.weight == 2) {
      w2[u].push_back(v);
      w2[v].push_back(u);
    }
    else assert(me.weight == 0);

    cout << p.first+1 << ' ' << p.second+1 << '\n';
    for (int i: me.ids) {
      cout << i << ": " << me.isFlipped[i] << ' ' << me.direction[i] << endl;
    }
  }

  cout << "weight 1:\n";
  for (int i = 0; i < n; i++) {
    for (int j: w1[i]) {
      if (i < j)
        cout << i+1 << ' ' << j+1 << '\n';
    }
  }

  cout << "weight 2:\n";
  for (int i = 0; i < n; i++) {
    for (int j: w2[i]) {
      if (i < j) 
        cout << i+1 << ' ' << j+1 << '\n';
    }
  }
  cout << "---\n";
      
  // Calculate the answer
  int answer = solve(n, w1, w2, sum, direction);


  vector<int> inout(n, 0);
  // Uncondense edges
  vector<int> ans(m, 0);
  for (auto [p, b]: direction) {
    for (auto [i, s]: multi_edges[p].uncompress(b)) {
      ans[i] = s ? 1 : 2;

      if (s^multi_edges[p].isFlipped[i]) {
        inout[p.first] -= weights[i];
        inout[p.second] += weights[i];
      }
      else {
        inout[p.first] += weights[i];
        inout[p.second] -= weights[i];
      }
    }
  }

  //output
  cout << answer << '\n';
  for (int i = 0; i < m; i++) {
    cout << ans[i];
  }
  cout << '\n';

  for (auto [p, b]: direction) {
    cout << p.first+1 << ' ' << p.second+1 << ": " << b << endl;
  }

  cout << inout << endl;
  for (int i = 0; i < n; i++) {
    if (sum[i] % 2 == 1) {
      cout << i << ' ' << inout[i] << endl;
      assert(abs(inout[i]) == 1);
    }
  }
  //assert(count(all(inout), -1) + count(all(inout), 1) == answer);
}

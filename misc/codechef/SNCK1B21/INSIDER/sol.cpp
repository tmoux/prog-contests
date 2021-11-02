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

template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v)
{
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << " ";
  }
  return o;
}
// }}}

class IntervalTracker {
  private:
  int n;
  set<int> s[2]; //0 = hi, 1 = low
  set<int> starts;

  bool isStart(int index, int i) const {
    auto it = s[i].find(index);
    assert(it != s[i].end());
    if (it == s[i].begin()) return true;
    else {
      int prevIndex = *prev(it);
      auto it2 = s[i^1].lower_bound(index);
      if (it2 == s[i^1].begin()) return false;
      else {
        int otherIndex = *prev(it2);
        return prevIndex < otherIndex;
      }
    }
  }

  void updateIndex(int index, int i) {
    if (isStart(index, i)) {
      starts.insert(index);
    }
    else if (starts.count(index)) {
      starts.erase(index);
    }
  }

  void updateNextIndices(int index) {
    auto it = s[0].upper_bound(index);
    if (it != s[0].end()) updateIndex(*it, 0);

    it = s[1].upper_bound(index);
    if (it != s[1].end()) updateIndex(*it, 1);
  }
  
  public:
  // initially all start below
  IntervalTracker(int _n) : n(_n) {
    s[0].clear();
    s[1].clear();
    for (int i = 0; i < n; i++) {
      s[1].insert(i);
    }
    starts.insert(0);
  }

  void insertAbove(int index) {
    assert(!s[0].count(index));
    s[0].insert(index);
    updateIndex(index, 0);

    updateNextIndices(index);
  }

  void removeBelow(int index) {
    assert(s[1].count(index));
    if (starts.count(index)) starts.erase(index);
    s[1].erase(index);

    updateNextIndices(index);
  }

  int longestSubsequence() const {
    return sz(starts);
  }
};

void solve() {
  int N; cin >> N;
  const int INF = 2e9;
  vector<pair<int,int>> v;
  F0R(i, N) {
    int ai; cin >> ai;
    v.push_back({ai, i});
  }

  auto calc_mins = [N, INF](vector<pair<int,int>> v) -> vector<int> {
    IntervalTracker tracker(N);
    sort(all(v), greater<pair<int,int>>());
    set<int> values;
    for (auto [ai, _]: v) values.insert(ai+1);

    vector<int> ans(N+1, INF);

    int pt = 0;
    for (auto it = values.rbegin(); it != values.rend(); ++it) {
      int x = *it;
      while (pt < sz(v) && v[pt].first > x) {
        int index = v[pt].second;
        tracker.removeBelow(index);
        tracker.insertAbove(index);
        pt++;
      }

      vector<int> indicesToAdd;
      while (pt < sz(v) && v[pt].first == x) {
        int index = v[pt].second;
        tracker.removeBelow(index);
        indicesToAdd.push_back(index);
        pt++;
      }

      int subseqLength = tracker.longestSubsequence();
      ans[subseqLength] = x;

      for (int index: indicesToAdd) {
        tracker.insertAbove(index);
      }
    }

    for (int i = N-1; i >= 2; i--) {
      ckmin(ans[i], ans[i+1]);
    }
    return ans;
  };

  auto mins = calc_mins(v);
  for (auto& [ai, _]: v) ai = -ai;
  auto maxs = calc_mins(v);

  //output
  for (int i = 2; i <= N; i++) {
    cout << (mins[i] < INF ? mins[i] : -1) << ' ';
  }
  cout << '\n';

  for (int i = 2; i <= N; i++) {
    cout << (maxs[i] < INF ? -maxs[i] : -1) << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  //Data structure test
  /*
  IntervalTracker t(5);
  cout << t.longestSubsequence() << '\n';
  t.removeBelow(4);
  t.insertAbove(4);

  t.removeBelow(2);
  t.insertAbove(2);

  t.removeBelow(0);
  t.insertAbove(0);

  cout << t.longestSubsequence() << '\n';
  */

  int T; cin >> T;
  while (T--) solve();
}

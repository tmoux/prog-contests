#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const int maxn = 1e5+5;
int N, Q, A[maxn];

int freq[maxn];
list<pair<int, int>>::iterator its[maxn];
list<pair<int, int>> MP;

void add(int idx) {
  int x = A[idx];
  if (its[x]->second == 1) {
    its[x] = prev(MP.erase(its[x]));
  }
  else its[x]->second--;
  its[x] = next(its[x]);
  freq[x]++;
  if (its[x] != MP.end() && its[x]->first == freq[x]) {
    its[x]->second++;
  }
  else {
    its[x] = MP.insert(its[x], {freq[x], 1});
  }
}

void remove(int idx) {
  int x = A[idx];
  if (its[x]->second == 1) {
    its[x] = MP.erase(its[x]);
  }
  else its[x]->second--;
  freq[x]--;
  if (its[x] != MP.begin() && prev(its[x])->first == freq[x]) {
    its[x] = prev(its[x]);
    its[x]->second++;
  }
  else {
    its[x] = MP.insert(its[x], {freq[x], 1});
  }
}

int get_answer() {
  using T = pair<int, int>;
  queue<T> q1, q2;
  for (auto [x, c]: MP) if (x > 0) q1.push({x, c});

  int ans = 0;
  while (1) {
    if (q1.empty() && q2.empty()) break;
    auto getFirst = [&](queue<T>& q) {
      return q.empty() ? 1e9 : q.front().first;
    };
    auto F = [&](queue<T>& q) {
      auto [x, c] = q.front();
      assert(c > 1);
      q2.push({x*2, c/2});
      ans += x*2 * (c/2);
      if (c % 2 == 0) q.pop();
      else q.front().second = 1;
    };
    auto G = [&](queue<T>& q) -> bool {
      auto [x, c] = q.front(); q.pop();
      assert(c == 1);
      if (q1.empty() && q2.empty()) return true;
      int a = getFirst(q1);
      int b = getFirst(q2);
      if (a < b) {
        q2.push({x + a, 1});
        ans += x + a;
        if (q1.front().second == 1) q1.pop();
        else q1.front().second--;
      }
      else {
        q2.push({x + b, 1});
        ans += x + b;
        if (q2.front().second == 1) q2.pop();
        else q2.front().second--;
      }
      return false;
    };
    int a = getFirst(q1);
    int b = getFirst(q2);
    if (a < b) {
      if (q1.front().second > 1) F(q1);
      else if (G(q1)) break;
    }
    else {
      if (q2.front().second > 1) F(q2);
      else if (G(q2)) break;
    }
  }
  return ans;
}

int block_size = 350;

struct Query {
  int l, r, idx;
  bool operator<(Query other) const
  {
    return make_pair(l / block_size, r) <
      make_pair(other.l / block_size, other.r);
  }
};

vector<int> MO(vector<Query> queries) {
  vector<int> answers(queries.size());
  sort(queries.begin(), queries.end());

  MP.push_back({0, N});
  for (int i = 1; i <= 100000; i++) {
    its[i] = MP.begin();
  }

  int cur_l = 0;
  int cur_r = -1;
  // invariant: data structure will always reflect the range [cur_l, cur_r]
  for (Query q : queries) {
    while (cur_l > q.l) {
      cur_l--;
      add(cur_l);
    }
    while (cur_r < q.r) {
      cur_r++;
      add(cur_r);
    }
    while (cur_l < q.l) {
      remove(cur_l);
      cur_l++;
    }
    while (cur_r > q.r) {
      remove(cur_r);
      cur_r--;
    }
    answers[q.idx] = get_answer();
  }
  return answers;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) cin >> A[i];
  cin >> Q;

  vector<Query> queries;
  F0R(i, Q) {
    int l, r; cin >> l >> r;
    l--, r--;
    queries.push_back({l, r, i});
  }

  auto ans = MO(queries);
  F0R(i, Q) {
    cout << ans[i] << '\n';
  }
}

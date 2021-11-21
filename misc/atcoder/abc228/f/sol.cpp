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

const int maxn = 1005;
int N, M;
int A[maxn][maxn];
int h1, w1, h2, w2;

ll pfx[maxn][maxn];
ll rec_sum(int r, int c, int H, int W) {
  ll ans = pfx[r+H-1][c+W-1];
  ans -= pfx[r-1][c+W-1];
  ans -= pfx[r+H-1][c-1];
  ans += pfx[r-1][c-1];
  return ans;
}

ll white_rec_sum[maxn][maxn];
ll mx_sum[maxn][maxn];
ll col_max[maxn][maxn];

struct MaxQueue/*{{{*/
{
    deque<pair<ll,int>> q;
    int cnt_added = 0;
    int cnt_removed = 0;
    ll maximum() {
        assert(!q.empty());
        return q.front().first;
    }
    void push(ll new_element) { //add new element
        while (!q.empty() && q.back().first < new_element) {
            q.pop_back();
        }
        q.push_back({new_element,cnt_added});
        cnt_added++;
    }
    void pop() {
        if (!q.empty() && q.front().second == cnt_removed) {
            q.pop_front();
        }
        cnt_removed++;
    }
};/*}}}*/

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> h1 >> w1 >> h2 >> w2;
  ckmin(h2, h1);
  ckmin(w2, w1);

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      cin >> A[i][j];
    }
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      pfx[i][j] = pfx[i-1][j] + pfx[i][j-1] - pfx[i-1][j-1] + A[i][j];
    }
  }

  for (int i = 1; i+h2-1 <= N; i++) {
    for (int j = 1; j+w2-1 <= M; j++) {
      white_rec_sum[i][j] = rec_sum(i, j, h2, w2);
    }
  }

  for (int i = 1; i+h2-1 <= N; i++) {
    //mx_sum[i]
    MaxQueue mq;
    for (int j = M-w2+1; j >= 1; j--) {
      mq.push(white_rec_sum[i][j]);
      if (j+(w1-w2+1) <= M-w2+1) mq.pop();
      mx_sum[i][j] = mq.maximum();
    }
  }
  for (int j = 1; j+w2-1 <= M; j++) {
    MaxQueue mq;
    for (int i = N-h2+1; i >= 1; i--) {
      mq.push(mx_sum[i][j]);
      if (i+(h1-h2+1) <= N-h2+1) mq.pop();
      col_max[i][j] = mq.maximum();
    }
  }

  ll ans = 0;
  for (int i = 1; i+h1-1 <= N; i++) {
    for (int j = 1; j+w1-1 <= M; j++) {
      ll black_sum = rec_sum(i, j, h1, w1);
      ll white_sum = col_max[i][j];
      ll sum = black_sum - white_sum;
      ckmax(ans, sum);
    }
  }

  cout << ans << '\n';
}

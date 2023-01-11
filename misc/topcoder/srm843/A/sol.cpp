#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
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
// }}}

class ChristmasSongTrauma {
public:
  double fewest(vector<int> playTime, int visitTime) {
    ll totalTime = std::accumulate(all(playTime), 0LL);
    ll minTime = *min_element(all(playTime));
    if (visitTime >= totalTime - minTime) {
      return 1.0;
    }
    int N = playTime.size();
    vector<ll> pfx(3 * N);
    for (int i = 0; i < 3 * N; i++) {
      pfx[i] = playTime[i % N] + (i == 0 ? 0 : pfx[i-1]);
    }
    int minSongs = N;

    for (int i = 0; i < N; i++) {
      ll s = i == 0 ? 0 : pfx[i-1];
      int j = i;
      while (pfx[j] - s < visitTime) {
        j++;
      }
      ckmin(minSongs, j - i + 1);
    }

    ll num = 0;
    for (int i = 0; i < N; i++) {
      ll s = i == 0 ? 0 : pfx[i-1];
      int j = i;
      while (pfx[j] - s < visitTime) {
        j++;
      }
      if (j - i + 1 == minSongs) {
        ll add = min((ll)playTime[i], pfx[j] - (s + visitTime) + 1);
        num += add;
      }
    }

    return (double) num / totalTime;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  ChristmasSongTrauma test;
  vector<int> playTime = {50, 100, 100};
  int visitTime = 201;
  cout << fixed << setprecision(10) << test.fewest(playTime, visitTime) << '\n';
}

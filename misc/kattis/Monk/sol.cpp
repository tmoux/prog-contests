#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<pair<int, int>> A(N), B(M);
  int total = 0;
  for (int i = 0; i < N; i++) {
    cin >> A[i].first >> A[i].second;
    total += A[i].first;
  }
  for (int i = 0; i < M; i++) {
    cin >> B[i].first >> B[i].second;
  }

  auto pos = [&](double t, const vector<pair<int, int>>& v) -> double {
    double H = 0;
    for (auto [h, ti]: v) {
      if (t >= ti) {
        t -= ti;
        H += h;
      }
      else {
        H += h * t / ti;
        break;
      }
    }
    return H;
  };

  double lo = 0, hi = 5000 * 100;
  for (int i = 0; i < 100; i++) {
    double mid = (lo + hi)/2;
    double up = pos(mid, A);
    double down = total - pos(mid, B);
    (up < down ? lo : hi) = mid;
  }
  cout << fixed << setprecision(10) << lo << '\n';
}

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll MOD = 998244353;
ll expo(ll a, ll n) {
  ll r = 1;
  while (n) {
    r = (r * a) % MOD;
    a = (a * a) % MOD;
    n >>= 1;
  }
  return r;
}
int main() {
  ll w, k;
  cin >> w >> k;
  vector<int> mob(k + 1), sv(k + 1);
  for (auto &v : mob) v = 1;
  for (ll p = 2; p <= k; p++)
    if (sv[p] == 0) {
      for (ll t = p; t <= k; t += p) {
        sv[t] = 1;
        mob[t] *= -1;
      }
      for (ll t = p * p; t <= k; t += p * p) mob[t] = 0;
    }
  ll s = 1;
  for (ll i = 1; i <= k; i++)
    s = (s + MOD + mob[i] * (expo(k / i * 2 + 1, w) - 1)) % MOD;
  cout << s << endl;
}

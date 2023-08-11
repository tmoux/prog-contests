#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+6;
int spf[maxn];
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uint64_t H[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
    for (int j = i; j < maxn; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }

  for (int i = 2; i < maxn; i++) {
    if (spf[i] == i) {
      H[i] = rng();
    }
    else {
      H[i] = H[spf[i]] ^ H[i/spf[i]];
    }
  }
}

int main() {
  init_spf();
  int n; cin >> n;
  vector<bool> ans(n+1, true);
  int N = n;
  map<uint64_t, int> mp;
  vector<uint64_t> hashes(n+1, 0);
  uint64_t hash = 0;
  for (int i = 1; i <= n; i++) {
    hashes[i] = hashes[i-1] ^ H[i];
    mp[hashes[i]] = i;
    hash ^= hashes[i];
  }

  if (hash) {
    if (mp.count(hash)) {
      int i = mp[hash];
      ans[i] = false;
      N--;
    }
    else {
      bool flag = false;
      for (int i = 1; i <= n; i++) {
        if (mp.count(hash ^ hashes[i])) {
          int j = mp[hash ^ hashes[i]];
          ans[i] = ans[j] = false;
          N -= 2;
          flag = true;
          break;
        }
      }

      if (!flag) {
        assert(n % 4 == 3);
        ans[n] = false;
        ans[(n-1)/2] = false;
        ans[2] = false;
        N -= 3;
      }
    }
  }

  cout << N << '\n';
  for (int i = 1; i <= n; i++) {
    if (ans[i]) cout << i << ' ';
  }
  cout << '\n';
}

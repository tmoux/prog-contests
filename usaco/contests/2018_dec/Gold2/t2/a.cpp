#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 50005;
int N;
int a[maxn][5];

ll ch2(ll x) {
  return x*(x-1)/2;
}

//This is faster than using a plain old vector<int>.
//Likely due to no heap allocations?
struct sub {
  int a[5];
  int sz = 0;
};

bool operator<(const sub& lhs, const sub& rhs) {
  for (int i = 0; i < 5; i++) {
    if (lhs.a[i] != rhs.a[i]) 
      return lhs.a[i] < rhs.a[i];
  }
  return false;
}

map<sub,int> mp;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  freopen("cowpatibility.in","r",stdin); freopen("cowpatibility.out","w",stdout);
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 5; j++) {
      cin >> a[i][j];
    }
    sort(a[i],a[i]+5);
  }

  auto getSub = [](int *arr, int mask) {
    sub ret = {{0,0,0,0,0},0};
    for (int i = 0; i < 5; i++) {
      if (mask & (1<<i)) ret.a[ret.sz++] = arr[i];
    }
    return ret;
  };
  for (int i = 0; i < N; i++) {
    for (int mask = 1; mask < (1<<5); mask++) {
      auto v = getSub(a[i],mask);
      mp[v]++;
    }
  }

  ll ans = 0;

  for (auto& p: mp) {
    int c = p.first.sz&1 ? 1 : -1;
    ans += c*ch2(p.second);
  }

  cout << ch2(N)-ans << '\n';
}

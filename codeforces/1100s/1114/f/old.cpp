#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4e5+5;
int n, q, a[maxn]; 

struct Node {
  //sqrt decomposition for a given prime p
  vector<int> bucket, lazy, val;
  vector<ll> bucketSum;
  int sz, sq;
  Node() {}
  Node(int a) {
    sz = n;
    sq = sqrt(sz) + 1;
    bucket.resize(sz+2,0);
    val.resize(sz+2,0);
    for (int i = 1; i <= sz; i++) {
      bucket[i] = (i-1)/sq + 1;
    }
    bucketSum.resize(bucket[sz]+2,0);
    lazy.resize(bucket[sz]+2,0);
  }
  void add(int l, int r, int x) {
    while (l > 1 && l <= r && bucket[l] == bucket[l-1]) {
      bucketSum[bucket[l]] += x;
      val[l] += x;
      l++;
    }
    if (l > r) return;
    while (bucket[l] < bucket[r]) {
      lazy[bucket[l]] += x;
      //update(l);
      l += sq;
    }
    for (int i = l; i <= r; i++) {
      bucketSum[bucket[i]] += x;
      val[i] += x;
    }
  }

  void update(int i) {
    int b = bucket[i];
    if (!lazy[b]) return;
    for (int j = i; j >= 1 && bucket[j] == b; j--) {
      val[j] += lazy[b];
      bucketSum[b] += lazy[b];
    }
    for (int j = i + 1; j <= n && bucket[j] == b; j++) {
      val[j] += lazy[b];
      bucketSum[b] += lazy[b];
    }
    lazy[b] = 0;
  }

  int getsum(int l, int r) {
    update(l);
    update(r);
    ll res = 0;
    while (l > 1 && l <= r && bucket[l] == bucket[l-1]) {
      res += val[l++];
    }
    while (bucket[l] < bucket[r]) {
      res += bucketSum[bucket[l]] + lazy[bucket[l]]*sq;
      l += sq;
    }
    for (int i = l; i <= r; i++) {
      res += val[i];
    }
    return res;
  }
};

vector<pair<int,int>> pfacs[305]; //{prime,cnt}
Node seg[305];
vector<int> primes;

void factor(int i, int orig) {
  for (int j = 2; j*j <= i; j++) {
    if (i % j == 0) {
      int cnt = 0;
      while (i % j == 0) {
        cnt++;
        i /= j;
      }
      pfacs[orig].push_back({j,cnt});
      factor(i,orig);
      return;
    }
  }
  if (i > 1) {
    pfacs[orig].push_back({i,1});
  }
}

void precomp() {
  for (int i = 1; i <= 300; i++) {
    factor(i,i);
    if (pfacs[i].size() == 1 && pfacs[i][0].second == 1) {
      primes.push_back(i);
      seg[i] = Node(1);
    }
  }

}

const int M = 1e9+7;
int mult(int a, int b) {
  return (1LL*a*b) % M;
}

ll modexp(ll x, ll n) {
  if (n == 0) return 1;
  if (n == 1) return x%M;
  if (n%2==0) return modexp((x*x)%M,n/2);
  return (x*modexp((x*x)%M,n/2))%M;
}

int main()
{
  cin >> n >> q;        
  precomp();
  for (int i = 1; i <= n; i++) {
    //int ai; ai = rand() % 300 + 1;
    int ai; cin >> ai;
    for (auto p: pfacs[ai]) {
      //if (i % 40000 == 0) cout << p.first << '\n';
      seg[p.first].add(i,i,p.second);
    }
  }
  while (q--) {
    string s; cin >> s;
    if (s == "TOTIENT") {
      int l, r; cin >> l >> r;
      int res = 1;
      for (int p: primes) {
        int cnt = seg[p].getsum(l,r);
        if (cnt == 0) continue;
        ll pn1 = modexp(p,cnt-1);
        int totient = mult((int)pn1,p-1);
        res = mult(res,totient);
      }
      cout << res << '\n';
    }
    else {
      int l, r, x; cin >> l >> r >> x;
      for (auto p: pfacs[x]) {
        seg[p.first].add(l,r,p.second);
      }
    }
  }
}

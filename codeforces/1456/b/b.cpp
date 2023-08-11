#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void amax(int& a, int b) {
  a = max(a,b);
}
void amin(int& a, int b) {
  a = min(a,b);
}

const int INF = 1000000000;
const int k = 35;
struct Trie {
  int mx_index, mn_index;
  Trie* nxt[2];
  Trie() {
    mx_index = -1;
    mn_index = INF;
    nxt[0] = nxt[1] = NULL;
  }
  
  void insert(ll x, int i, int idx) {
    bool b = x&(1LL<<i);  
    if (i >= 0) {
      if (!nxt[b]) nxt[b] = new Trie();
      nxt[b]->insert(x,i-1,idx);
      mx_index = max(mx_index,nxt[b]->mx_index);
      mn_index = min(mn_index,nxt[b]->mn_index);
    }
    else {
      mx_index = max(mx_index,idx);
      mn_index = min(mn_index,idx);
    }
  }

  int calc(ll xr, ll target, int i) {
    if (i < 0) {
      return -1;
    }
    bool b1 = xr&(1LL<<i);
    bool b2 = target&(1LL<<i);
    int ret = -1;
    if (!b1 && !b2) {
      if (nxt[0]) amax(ret,nxt[0]->calc(xr,target,i-1));
      if (nxt[1]) amax(ret,nxt[1]->mx_index);
    }
    else if (!b1 && b2) {
      if (nxt[1]) amax(ret,nxt[1]->calc(xr,target,i-1));
    }
    else if (b1 && !b2) {
      if (nxt[0]) amax(ret,nxt[0]->mx_index);
      if (nxt[1]) amax(ret,nxt[1]->calc(xr,target,i-1));
    }
    else if (b1 && b2) {
      if (nxt[0]) amax(ret,nxt[0]->calc(xr,target,i-1));
    }
    return ret;
  }

  int calc2(ll xr, ll target, int i) {
    if (i < 0) {
      return INF;
    }
    bool b1 = xr&(1LL<<i);
    bool b2 = target&(1LL<<i);
    int ret = INF;
    if (!b1 && !b2) {
      if (nxt[0]) amin(ret,nxt[0]->calc2(xr,target,i-1));
    }
    else if (!b1 && b2) {
      if (nxt[0]) amin(ret,nxt[0]->mn_index);
      if (nxt[1]) amin(ret,nxt[1]->calc2(xr,target,i-1));
    }
    else if (b1 && !b2) {
      if (nxt[1]) amin(ret,nxt[1]->calc2(xr,target,i-1));
    }
    else if (b1 && b2) {
      if (nxt[0]) amin(ret,nxt[0]->calc2(xr,target,i-1));
      if (nxt[1]) amin(ret,nxt[1]->mn_index);
    }
    return ret;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<ll> a(n+1,0), xo(n+1,0), ox(n+2,0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    xo[i] = a[i];
    xo[i] ^= xo[i-1];
  }
  for (int i = n; i >= 1; i--) {
    ox[i] = a[i];
    ox[i] ^= ox[i+1];
  }
  int ans = INF;

  Trie *root = new Trie();
  for (int i = 1; i < n; i++) {
    root->insert(xo[i-1],k,i-1);
    int c = root->calc(xo[i],a[i+1],k);
    if (c != -1) ans = min(ans,i-c-1);
  }

  root = new Trie();
  for (int i = n; i > 1; i--) {
    root->insert(ox[i+1],k,i+1);
    int c = root->calc2(ox[i],a[i-1],k);
    if (c != INF) ans = min(ans,c-i-1);
  }
  assert(ans != 0);
  cout << (ans>=INF?-1:ans) << '\n';
}

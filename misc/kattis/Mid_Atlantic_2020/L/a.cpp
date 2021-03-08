#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, K; cin >> n >> K;
  bool can[26][26];
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      can[i][j] = i != j;
    }
  }
  vector<string> v;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    v.push_back(s);
    for (int j = 0; j < K; j++) {
      for (int k = j+1; k < K; k++) {
        can[s[k]-'A'][s[j]-'A'] = false;
      }
    }
  }
  vector<int> ans(K);
  for (int i = 0; i < K; i++) {
    ans[i] = 1;
    for (int j = 0; j < i; j++) {
      if (can[v[0][j]-'A'][v[0][i]-'A']) {
        ans[i] = max(ans[i],ans[j]+1);
      }
    }
  }
  cout << *max_element(ans.begin(),ans.end()) << '\n';
}

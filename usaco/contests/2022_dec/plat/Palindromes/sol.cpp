#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 7505;
int N;
string S;
int cntG[maxn], cntH[maxn];

int cnt(string s) {
  if (s.empty() || s.size() == 1) return 0;
  else if (s[0] == s.back()) {
    return cnt(s.substr(1, s.size() - 2));
  }
  else {
    int i = s.size() - 1;
    while (i >= 0 && s[i] != s[0]) i--;

    int j = 0;
    while (j < (int)s.size() && s[j] != s.back()) j++;

    int s1 = s.size() - 1 - i;
    int s2 = j;

    if (s1 < s2) {
      swap(s[i], s[s.size()-1]);
      return s1 + cnt(s.substr(1, s.size() - 2));
    }
    else {
      swap(s[0], s[j]);
      return s2 + cnt(s.substr(1, s.size() - 2));
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> S;
  N = S.size();

  for (int i = 0; i < N; i++) {
    cntG[i] = (i == 0 ? 0 : cntG[i-1]) + (S[i] == 'G');
    cntH[i] = (i == 0 ? 0 : cntH[i-1]) + (S[i] == 'H');
  }

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
      int cg = cntG[j] - (i == 0 ? 0 : cntG[i-1]);
      int ch = cntH[j] - (i == 0 ? 0 : cntH[i-1]);

      string s = S.substr(i, j - i + 1);
      if (cg % 2 == 0 || ch % 2 == 0) {
        ans += cnt(s);
      }
      else {
        ans--;
      }
    }
  }

  cout << ans << '\n';
}

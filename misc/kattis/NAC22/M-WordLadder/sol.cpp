#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

string mutate(string s) {
  int N = s.size();
  int i = rng() % N;
  char c;
  do {
    c = (rng() % 26) + 'a';
  } while (c == s[i]);
  s[i] = c;
  return s;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<string> ans;
  set<string> s;
  ans.push_back(string(10, 'a'));
  s.insert(string(10, 'a'));

  auto count_diff = [&](const string& s, const string& t) -> int {
    int r = 0;
    for (int i = 0; i < (int)s.size(); i++) {
      if (s[i] != t[i]) r++;
    }
    return r;
  };

  auto is_valid = [&](const string& t, int k) -> bool {
    for (int i = 0; i < k; i++) {
      if (count_diff(ans[i], t) <= 1) return false;
    }
    return true;
  };

  for (int i = 1; i < N; i++) {
    string t;
    do {
      t = mutate(ans.back());
    } while (s.count(t) || !is_valid(t, i-1));
    s.insert(t);
    ans.push_back(t);
  }

  for (string s: ans) {
    cout << s << '\n';
  }
}

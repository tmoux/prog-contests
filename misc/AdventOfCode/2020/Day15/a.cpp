#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  vector<int> v = {15,5,1,4,7,0};
  map<int,deque<int>> mp;
  for (int i = 1; i <= (int)v.size(); i++) {
    mp[v[i-1]].push_back(i);
  }
  int last = 0;
  for (int i = 7; i <= 30000000; i++) {
    if (mp[last].size() >= 2) {
      int sz = mp[last].size();
      last = mp[last][sz-1]-mp[last][sz-2];
    }
    else {
      last = 0;
    }
    mp[last].push_back(i);
    if ((int)mp[last].size() >= 3) {
      mp[last].pop_front();
    }
    if (i % 1000000 == 0)
      cout << i << ": " << last << endl;
  }
  cout << last << '\n';
}

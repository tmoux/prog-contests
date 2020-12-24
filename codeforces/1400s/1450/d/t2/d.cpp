#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct MinQueue
{
    deque<pair<int,int>> q;
    int cnt_added = 0;
    int cnt_removed = 0;
    int minimum() {
        assert(!q.empty());
        return q.front().first;
    }
    void push(int new_element) { //add new element
        while (!q.empty() && q.back().first > new_element) {
            q.pop_back();
        }
        q.push_back({new_element,cnt_added});
        cnt_added++;
    }
    void pop() {
        if (!q.empty() && q.front().second == cnt_removed) {
            q.pop_front();
        }
        cnt_removed++;
    }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& i: a) cin >> i;

    auto check = [&n,&a](int len) {
      vector<int> b;
      MinQueue q;  
      for (int i = 0; i < len; i++) {
        q.push(a[i]);
      }
      b.push_back(q.minimum());
      for (int i = len; i < n; i++) {
        q.pop();
        q.push(a[i]);
        b.push_back(q.minimum());
      }
      vector<int> cnt(n+1,0);
      if (*max_element(b.begin(),b.end()) != (int)b.size())
        return false;
      for (int i = 0; i < (int)b.size(); i++) {
        if (++cnt[b[i]] > 1) return false;
      }
      return true;
    };
    int lo = 1, hi = n+1;
    while (lo+1 < hi) {
      int mid = (lo+hi)/2;
      if (check(mid)) {
        hi = mid;
      }
      else {
        lo = mid;
      }
    }

    //output
    cout << check(1);
    for (int i = 2; i <= lo; i++) cout << 0;
    for (int i = lo+1; i <= n; i++) cout << 1;
    cout << endl;
  }
}


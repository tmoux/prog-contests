namespace Euler {
  typedef vector<pair<int,int>> vpi;
  const int MX = 4e5+5;
  int N, M;
  vector<vpi> graph(MX); //{ed, edNum}
  vector<vpi::iterator> its(MX);
  vector<bool> used(MX);

  // This assume the graph is connected!
  // Returns a vector of (node, edge index)
  vpi eulerPath(int r) {
      F0R(i, N) its[i] = begin(graph[i]);
      F0R(i, M) used[i] = false;
      vpi ans, s{{r, -1}};
      int lst = -1;
      while (sz(s)) {
          int x = s.back().first; auto &it = its[x], en = end(graph[x]);
          while (it != en && used[it->second]) it++;

          if (it == en) {
              if (lst != -1 && lst != x) return {};
              ans.push_back(s.back()); s.pop_back(); if (sz(s)) lst = s.back().first;
          } else {
              s.push_back(*it);
              used[it->second] = 1;
          }
      }
      if (sz(ans) != M+1) return {};
      return ans;
  }
};
using namespace Euler;

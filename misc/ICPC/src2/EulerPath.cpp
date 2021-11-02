int N, M;
vector<vpi> graph(MX); //{ed, edNum}
vector<vpi::iterator> its(MX);
vector<bool> used(MX);

vpi eulerPath(int r) {
    F0R(i, N) its[i] = begin(graph[i]);
    F0R(i, M) used[i] = false;
    vpi ans, s{{r, -1}};
    int lst = -1;
    while (sz(s)) {
        int x = s.back().f; auto &it = its[x], en = end(graph[x]);
        while (it != en && used[it->s]) it++;

        if (it == en) {
            if (lst != -1 && lst != x) return {};
            ans.pb(s.back()); s.pop_back(); if (sz(s)) lst = s.back().f;
        } else {
            s.pb(*it);
            used[it->s] = 1;
        }
    }
    if (sz(ans) != M+1) return {};
    return ans;
}

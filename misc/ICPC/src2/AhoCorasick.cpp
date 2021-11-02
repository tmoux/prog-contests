struct AhoCorasick {
    static const int K = 26;

    struct Vertex {
        int next[K];
        bool leaf = false;
        int p = -1;
        char pch;
        int link = -1;
        int go[K];
        ll value = -1;
        ll num = 0;

        Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
            fill(begin(next), end(next), -1);
            fill(begin(go), end(go), -1);
        }
    };

    vector<Vertex> t;

    void init() {
        Vertex v; t.pb(v);
    }



    void add_string(string const& s, int count) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) {
                t[v].next[c] = t.size();
                t.emplace_back(v, ch);
            }
            v = t[v].next[c];
        }
        t[v].leaf = true;
        t[v].num = count;
    }

    ll dfs(int v) {
        if (t[v].value != -1) {
            return t[v].value;
        }
        ll ans = t[v].num;
        ans += dfs(get_link(v)); // is this right?
        return t[v].value = ans;
    }

    void compute() {
        t[0].value = 0;
        FOR(i, 1, sz(t)) {
            dfs(i);
        }
    }

    int get_link(int v) {
        if (t[v].link == -1) {
            if (v == 0 || t[v].p == 0)
                t[v].link = 0;
            else
                t[v].link = go(get_link(t[v].p), t[v].pch);
        }
        return t[v].link;
    }

    int go(int v, char ch) {
        int c = ch - 'a';
        if (t[v].go[c] == -1) {
            if (t[v].next[c] != -1)
                t[v].go[c] = t[v].next[c];
            else
                t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
        }
        return t[v].go[c];
    }
};
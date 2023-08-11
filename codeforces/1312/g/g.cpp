#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Seg
{
    vector<int> v = {2000000000};
    int aux = 0;
    void add(int x) {
        v.push_back(min(v.back(),x-aux));
    }
    int getmin() {
        return v.back()+aux;
    }
    void pop() {
        v.pop_back();
    }
};
Seg seg;

const int maxn = 1e6+6;
int n, k;
struct TNode
{
    TNode *nxt[26];
    TNode *anc;
    bool special, used;
    TNode(TNode *a) {
        for (int i = 0; i < 26; i++) {
            anc = a;
            nxt[i] = NULL;
            special = false;
            used = false;
        }
    }
    TNode* insert(char c) {
        if (!nxt[c-'a']) nxt[c-'a'] = new TNode(this);
        return nxt[c-'a'];
    }
    void update(bool is) {
        if (is) special = is;
        if (used) return;
        used = true;
        if (anc) anc->update(false);
    }
};
TNode *root;

int t = 0;
set<TNode*> specials;
map<TNode*,int> ans;
int depth[maxn];
void dfs(TNode *curr, TNode *par, int d) {
    depth[++t] = d;
    bool isSpecial = specials.count(curr);
    if (curr != root) {
        ans[curr] = ans[par] + 1;
        if (isSpecial) {
            ans[curr] = min(ans[curr],seg.getmin());
        }
    }
    //cout << t << ": " << ans[curr] << endl;
    //update segtree
    seg.add(ans[curr]+1);
    if (isSpecial) {
        seg.aux++;
    }
    for (int i = 0; i < 26; i++) {
        if (!curr->nxt[i] || !curr->nxt[i]->used) continue;
        dfs(curr->nxt[i],curr,d+1);
    }
    seg.pop();
}

bool special[maxn];
vector<int> adj[maxn];
int buildTree(TNode *curr, int d) {
    depth[++t] = d;
    special[t] = specials.count(curr);
    int ret = t;
    for (int i = 0; i < 26; i++) {
        if (!curr->nxt[i] || !curr->nxt[i]->used) continue;
        adj[t].push_back(buildTree(curr->nxt[i],curr,d+1));
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    root = new TNode(NULL);
    vector<TNode*> v = {root};
    for (int i = 1; i <= n; i++) {
        int pi; cin >> pi;
        char ci; cin >> ci;
        v.push_back(v[pi]->insert(ci));
    }
    cin >> k;
    map<int,TNode*> ord;
    for (int i = 0; i < k; i++) {
        int ai; cin >> ai;
        v[ai]->update(true);
        specials.insert(v[ai]);
        ord[i] = v[ai];
        //cout << v[ai]->special << endl;
    }

    ans[root] = 0;
    dfs(root,NULL,0);
    //output
    for (int i = 0; i < k; i++) {
        cout << ans[ord[i]] << ' ';
    }
    cout << '\n';
}

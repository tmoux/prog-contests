#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5+5, sz = 26;
int n, ans = 0;
struct Edge { int to, letter; };
vector<Edge> adj[maxn];

struct Path { bitset<sz> bits; int len; };
struct Trie
{
    Trie* nxt[2];
    int len;
    Trie() {
        len = 0;
        nxt[0] = NULL, nxt[1] = NULL;
    }
};

void addTrie(Trie* root, const Path& p) {
    for (int i = 0; i < sz; i++) {
        bool as = p.bits[i];
        if (!root->nxt[as]) root->nxt[as] = new Trie();
        root = root->nxt[as];
    }
    root->len = max(root->len,p.len);
}

int max_pali(Trie* curr, const bitset<sz>& bits, int idx=0, int cnt=1) {
    if (idx == sz) return curr->len;
    bool as = bits[idx];
    if (cnt == 0) {
        if (curr->nxt[as]) return max_pali(curr->nxt[as],bits,idx+1,cnt);
        return 0;
    }
    else {
        int res = 0;
        if (curr->nxt[as]) res = max_pali(curr->nxt[as],bits,idx+1,cnt);
        if (curr->nxt[!as]) res = max(res,max_pali(curr->nxt[!as],bits,idx+1,0));
        return res;
    }
}

struct Node
{
    Trie* trie;
    vector<Path> vec;
    bitset<sz> aux;
    int laux;
    inline int size() { return vec.size(); }
    Node() {
        trie = new Trie();
        laux = 0;
    }
    void pullup(int letter) { //adds to aux, adds path to trie
        Path p = {bitset<sz>(),0};
        insert(p);
        laux++;
        aux.flip(letter);
    }
    inline void convert(bitset<sz>& bits) {
        for (int i = 0; i < sz; i++) if (aux[i]) bits[i].flip();
    }
    Path& extract(Path& p) {
        convert(p.bits);
        p.len += laux;
        return p;
    }
    void insert(Path& p) {
        convert(p.bits);
        p.len -= laux;
        vec.push_back(p);
        addTrie(trie,p);
    }
};

void merge(Node& a, Node& b) {
    if (a.size() < b.size()) swap(a,b);
    for (Path& p: b.vec) {
        p = b.extract(p);
        a.convert(p.bits);
        ans = max(ans,max_pali(a.trie,p.bits) + p.len + a.laux);
    }
    for (Path& p: b.vec) {
        a.insert(b.extract(p));
    }
}

Node* dfs(int i, int par) {
    Node* ni = new Node();
    for (Edge e: adj[i]) {
        if (e.to == par) continue;
        Node* nj = dfs(e.to,i);
        nj->pullup(e.letter);
        merge(*ni,*nj);
        delete nj;
    }
    cout << i << ": laux: " << ni->laux << '\n';
    cout << ni->aux << '\n';
    for (Path& p: ni->vec) {
        p = ni->extract(p);
        cout << p.bits.to_string() << ' ' << p.len << '\n';
    }
    return ni;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int pi; char ci; cin >> pi >> ci;
        adj[i].push_back({pi,ci-'a'});
        adj[pi].push_back({i,ci-'a'});
    }

    dfs(1,1);

    return 0;
}
	


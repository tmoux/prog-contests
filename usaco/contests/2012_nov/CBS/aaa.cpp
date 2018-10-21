#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;

#define RA(x) begin(x), end(x)
#define FE(i, x) for (auto i = begin(x); i != end(x); ++i)
#define SZ(x) (x).size()

struct tree
{
    int top;
    int height = 0, height2 = 0;
    int hchild = -1;
};

struct tnode
{
    int tid;
    int depth;
};

struct node
{
    bool used = false;
    vi edges;
    int size = 1;
    vector<tnode> tnodes;
};

static vector<node> nodes;
static vector<tree> trees;

static int dfs_size(int cur, int parent)
{
    nodes[cur].size = 1;
    for (int v : nodes[cur].edges)
        if (v != parent && !nodes[v].used)
            nodes[cur].size += dfs_size(v, cur);
    return nodes[cur].size;
}

static int find_cent(int cur, int parent, int full)
{
    for (int v : nodes[cur].edges)
        if (v != parent && !nodes[v].used)
            if (nodes[v].size * 2 >= full)
                return find_cent(v, cur, full);
    return cur;
}

static void dfs_depth(int cur, int parent, int tid, int depth)
{
    nodes[cur].tnodes.push_back(tnode{tid, depth});
    for (int v : nodes[cur].edges)
        if (v != parent && !nodes[v].used)
            dfs_depth(v, cur, tid, depth + 1);
}

static void make_tree(int top, int parent)
{
    dfs_size(top, parent);
    int c = find_cent(top, parent, nodes[top].size);
    tree &t = trees[c];
    t.top = top;
    nodes[c].used = true;
    dfs_depth(c, -1, c, 0);
    for (int v : nodes[c].edges)
        if (!nodes[v].used)
            make_tree(v, c);
}

int main(int argc, const char **argv)
{
    ifstream cin("newbarn.in");
    ofstream cout("newbarn.out");
    int Q;
    cin >> Q;
    vector<pii> commands;
    int N = 0;
    for (int i = 0; i < Q; i++)
    {
        char t;
        int k;
        cin >> t >> k;
        if (k > 0)
            k--;
        if (t == 'B')
        {
            commands.emplace_back(N, k);
            N++;
        }
        else
            commands.emplace_back(-1, k);
    }

    nodes.resize(N);
    trees.resize(N);
    vi roots;
    for (const auto &cmd : commands)
        if (cmd.first >= 0)
        {
            int v = cmd.first;
            if (cmd.second != -1)
            {
                int p = cmd.second;
                nodes[v].edges.push_back(p);
                nodes[p].edges.push_back(v);
            }
            else
                roots.push_back(v);
        }

    for (int r : roots)
        make_tree(r, -1);

    int active = 0;
    for (const auto &cmd : commands)
    {
        if (cmd.first >= 0)
        {
            int prev = -1;
            int v = active;
            assert(v == cmd.first);
            const node &n = nodes[v];
            for (int i = SZ(n.tnodes) - 1; i >= 0; i--)
            {
                const tnode &tn = n.tnodes[i];
                tree &t = trees[tn.tid];
                if (tn.depth > t.height)
                {
                    if (prev != t.hchild)
                        t.height2 = t.height;
                    t.height = tn.depth;
                    t.hchild = prev;
                }
                else if (tn.depth > t.height2 && prev != t.hchild)
                    t.height2 = tn.depth;
                prev = t.top;
            }
            active++;
        }
        else
        {
            int v = cmd.second;
            const node &n = nodes[v];
            int prev = -1;
            int ans = 0;
            for (int i = SZ(n.tnodes) - 1; i >= 0; i--)
            {
                const tnode &tn = n.tnodes[i];
                const tree &t = trees[tn.tid];
                if (tn.tid >= active)
                {
                    prev = t.top;
                    continue;
                }
                if (t.hchild != prev)
                    ans = max(ans, tn.depth + t.height);
                else
                    ans = max(ans, tn.depth + t.height2);
                prev = t.top;
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
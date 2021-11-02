#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 510000;
const int sigma = 26;

struct edge
{
    int v, next;
};

edge g[maxn << 1];
int trie[maxn << 1][sigma], fa[maxn << 1], maxi[maxn << 1], sizia[maxn << 1];
char str[maxn];
int head[maxn << 1];
int siz,last;

void insert(int u, int v)
{
    static int id;
    g[++id].v = v;
    g[id].next = head[u];
    head[u] = id;
}

//This is the core of SAM
void add(int id)
{
    int p = last;
    int np = last = ++siz;
    sizia[np] = 1;
    maxi[np] = maxi[p] + 1;
    while (p && !trie[p][id]){
        trie[p][id] = np;
        p = fa[p];
    }
    if (!p){
        fa[np] = 1;
    }
    else{
        int q = trie[p][id];
        if (maxi[p] + 1 == maxi[q]){
            fa[np] = q;
        }
        else{
            int nq = ++siz;
            maxi[nq] = maxi[p] + 1;
            memcpy(trie[nq], trie[q], sizeof trie[q]);
            fa[nq] = fa[q];
            fa[np] = fa[q] = nq;
            while (trie[p][id] == q){
                trie[p][id] = nq;
                p = fa[p];
            }
        }
    }
}

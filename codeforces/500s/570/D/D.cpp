#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_set>
using namespace std;
typedef long long ll;

int n, m;
struct Node
{
    vector<unordered_set<char>>* vec;
    inline int sz() {return vec->size();}
    Node() {
        vec = new vector<unordered_set<char>>;
    }

    void addlast(char c) {
        unordered_set<char> toadd;
        toadd.insert(c);
        vec->push_back(toadd);
    }

    bool getans(int curdep, int dep) {
        int newdep = dep - curdep;
        //cout << curdep << ' ' << dep << '\n';
        if (newdep < 0) return true;
        int idx = sz() - 1 - newdep;
        if (idx < 0) return true;
        return ((*vec)[idx].size() <= 1);
    }

    void cleanup() {
        delete vec;
    }
};

void merge(Node& a, Node& b) {
    if (a.sz() < b.sz()) swap(a,b);
    int diff = a.sz() - b.sz();
    for (int i = 0; i < b.sz(); i++) {
        for (char c: (*b.vec)[i]) {
            if ((*a.vec)[i+diff].count(c) != 0) {
                (*a.vec)[i+diff].erase(c);
            }
            else {
                (*a.vec)[i+diff].insert(c);
            }
        }
    }
    b.cleanup();
}
const int maxn = 500005;
vector<int> child[maxn];
char charat[maxn];
Node nodes[maxn];
int depth[maxn];
vector<pair<int,int>> queries[maxn];
bool ans[maxn];

void dfs(int i, int d) {
    depth[i] = d;
    nodes[i] = Node();
    for (int j: child[i]) {
        dfs(j,d+1);
        merge(nodes[i],nodes[j]);

    }
    //add our own node
    nodes[i].addlast(charat[i]);
    for (pair<int,int> p: queries[i]) {
        ans[p.second] = nodes[i].getans(depth[i],p.first);
        //cout << "getans " << i << ' ' << depth[i] << ' ' << p.first << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        int pi; cin >> pi;
        child[pi].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        cin >> charat[i];
    }
    for (int i = 0; i < m; i++) {
        int vi, hi; cin >> vi >> hi;
        queries[vi].push_back({hi,i});        
    }
    dfs(1,1);
    for (int i = 0; i < m; i++) {
        cout << (ans[i] ? "Yes" : "No") << '\n';
    }

    return 0;
}
	


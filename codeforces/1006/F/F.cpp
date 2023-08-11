#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 22;
const int maxk = 60;
int n, m;
ll k, grid[maxn][maxn];

struct Node
{
    int cnt;
    Node* child[2];
    Node() {
        cnt = 0;
        child[0] = NULL;
        child[1] = NULL;
    }
    void insert(ll curr, int i) {
        if (i < 0) {
            cnt++;
            return;
        }
        bool nxt = curr & (1LL << i);
        if (!child[nxt]) {
            child[nxt] = new Node();
        }
        child[nxt]->insert(curr,i-1);
    }
    int query(ll curr, int i) {
        if (i < 0) {
            return cnt;
        }
        bool nxt = curr & (1LL << i);
        if (!child[nxt]) return 0;
        return child[nxt]->query(curr,i-1);
    }

    void cleanup() {
        for (int i = 0; i < 2; i++) {
            if (child[i] != NULL) {
                child[i]->cleanup();
                delete child[i];
            }
        }
    }
};

void dfs1(int x1, int y1, int x2, int y2, ll curr, Node* root) {
    if (x1 == x2 && y1 == y2) {
        root->insert(curr,maxk);
        return;
        //cout << x1 << ' ' << y1 << ' ' << curr << '\n';
    }
    curr ^= grid[x1][y1];
    for (int i = 0; i < 2; i++) {
        int nx = x1 + i;
        int ny = y1 + (i^1);
        if (nx <= x2 && ny <= y2) {
            dfs1(nx,ny,x2,y2,curr,root);
        }
    }
}

void dfs2(int x, int y, ll curr, Node* root, ll& ans) {
    curr ^= grid[x][y];    
    if (x == n-1 && y == m-1) {
        ans += root->query(curr^k,maxk);
        return;
    }
    for (int i = 0; i < 2; i++) {
        int nx = x + i;
        int ny = y + (i^1);
        if (nx < n && ny < m) {
            dfs2(nx,ny,curr,root,ans);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        int r = n - 1 - i;
        int c = i;
        if (r < 0) break;
        Node* root = new Node();
        dfs1(0,0,r,c,0,root);
        dfs2(r,c,0,root,ans);    
        root->cleanup();
    }
    cout << ans << '\n';

    return 0;
}
	


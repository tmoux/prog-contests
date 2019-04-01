//#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
const int maxk = 18;
int n = 1;
vector<int> adj[maxn];
int par[maxk][maxn];
int depth[maxn];

void setFarmLocation(int id, int x, int y) {
    printf("%d: (%d, %d)\n",id,x,y);
}

void addBox(int x1, int y1, int x2, int y2) {
    printf("(%d, %d), (%d, %d)\n",x1,y1,x2,y2);
}

void addRoad(int a, int b){
    adj[a].push_back(b);
    adj[b].push_back(a);
    n++;
}

void DFS(int i, int p) {
    par[0][i] = p;
    for (int j: adj[i]) {
        if (j == p) continue;
        depth[j] = depth[i] + 1;
        DFS(j,i);
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = maxk - 1; k >= 0; k--) {
        int to = par[k][b];
        if (to != -1 && depth[to] >= depth[a]) {
            b = to;
        }
    }
    if (a == b) return a;
    for (int k = maxk - 1; k >= 0; k--) {
        int na = par[k][a];
        int nb = par[k][b];
        if (na != nb) {
            a = na;
            b = nb;
        }
    }
    return par[0][a];
}

int xs[maxn], ys[maxn]; //x-length and y-length of box needed
int relx[maxn], rely[maxn];
//relx[i] is how far to the left, rely[i] is how far down
void DFS2(int i, int p) {
    int cnt = 0;
    for (int j: adj[i]) {
        if (j == p) continue;
        cnt++;
        DFS2(j,i);
    }
    if (cnt == 0) {
        //leaf node
        xs[i] = 1;
        ys[i] = 1;
    }
    else {
        int y = 1;
        int x = 1;
        for (int j: adj[i]) {
            y += ys[j];
        }
        ys[i] = y;
        for (int j: adj[i]) {
            y -= ys[j];
            relx[j] = x;
            rely[j] = y;
            x += xs[j];
        }
        xs[i] = x;
    }
    cout << i << ": " << xs[i] << ' ' << ys[i] << '\n';
}

int px[maxn], py[maxn];

void DFS3(int i, int p) {
    for (int j: adj[i]) {
        if (j == p) continue;
        px[j] = px[i] - relx[j];
        py[j] = py[i] - rely[j];
        DFS3(j,i);
    }
}

void buildFarms(){
    //call setFarmLocation(id, x, y) for each farm
    memset(par,-1,sizeof par);
    DFS(0,-1);
    for (int k = 1; k < maxk; k++) {
        for (int i = 0; i < n; i++) {
            if (par[k-1][i] == -1) par[k][i] = -1;
            else par[k][i] = par[k-1][par[k-1][i]];
        }
    }
    DFS2(0,-1);
    //set 1 at rightmost top corner
    px[0] = n; py[0] = n;
    DFS3(0,-1);
    for (int i = 0; i < n; i++) {
        setFarmLocation(i,px[i],py[i]);    
    }
}

int walk(int b, int lc) {
    for (int k = maxk - 1; k >= 0; k--) {
        int to = par[k][b];
        if (to != -1 && depth[to] > lc) {
            b = to;
        }
    }
    return b;
}

void notifyFJ(int a, int b) {
    //call addBox(x1,y1,x2,y2) one or two times
    if (depth[a] > depth[b]) swap(a,b);
    int lc = lca(a,b);
    if (lc == a) {
        addBox(px[b],py[b],px[a],py[a]);
    }
    else {
        int c = walk(b,lc);
        addBox(px[a],py[a],px[lc],py[lc]);
        addBox(px[b],py[b],px[c],py[c]);
    }
}

int main()
{
    int n; cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        addRoad(a,b);
    }
    buildFarms();
    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        notifyFJ(a,b);
    }
}
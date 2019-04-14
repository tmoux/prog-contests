#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

////////////////
/*
int N, Q;
int getN() { return N;}
int getQ() { return Q;}
void setFarmLocation(int ID, int X, int Y) {
    printf("%d: (%d, %d)\n",ID,X,Y);
}
void addBox(int x1, int y1, int x2, int y2) {
    printf("(%d,%d), (%d,%d)\n",x1,y1,x2,y2);
}
*/
/////////////////
const int maxn = 1e5+5;
const int maxk = 18;
int n;
vector<int> adj[maxn];
int par[maxk][maxn];
int depth[maxn];

void addRoad(int a, int b){
    adj[a].push_back(b);
    adj[b].push_back(a);
}

int pre[maxn], post[maxn], pt = 1, pr = 1;

int px[maxn], py[maxn];
void DFS(int i, int p) {
    pre[i] = pt++;
    px[i] = pre[i];
    par[0][i] = p;
    for (int j: adj[i]) {
        if (j == p) continue;
        depth[j] = depth[i] + 1;
        DFS(j,i);
    }
    post[i] = pr++;
    py[i] = post[i];
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
            b = na;
        }
    }
    return par[0][a];
}


void buildFarms(){
    //call setFarmLocation(id, x, y) for each farm
    n = getN();
    memset(par,-1,sizeof par);
    DFS(0,-1);
    for (int k = 1; k < maxk; k++) {
        for (int i = 0; i < n; i++) {
            if (par[k-1][i] == -1) par[k][i] = -1;
            else par[k][i] = par[k-1][par[k-1][i]];
        }
    }
    for (int i = 0; i < n; i++) {
        setFarmLocation(i,pre[i],post[i]);    
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

void notifyFJ(int a, int b){
    //call addBox(x1,y1,x2,y2) one or two times
    if (depth[a] > depth[b]) swap(a,b);
    int lc = lca(a,b);
    if (lc == a) {
        addBox(px[a],py[b],px[b],py[a]);
    }
    else {
        int c = walk(b,lc);
        //printf("a = %d, b = %d, lca = %d, c = %d\n",a,b,lc,c);
        /*
        addBox(min(px[a],px[lc]),min(py[a],py[lc]),max(px[a],px[lc]),max(py[a],py[lc]));
        addBox(min(px[b],px[c]),min(py[b],py[c]),max(px[b],px[c]),max(py[b],py[c]));
        */
        addBox(px[lc],py[a],px[a],py[lc]);
        addBox(px[b],py[c],px[c],py[b]);
    }
}

/*
int main()
{
    cin >> N >> Q;
    for (int i = 0; i < N-1; i++) {
        int a, b; cin >> a >> b;
        addRoad(a,b);
    }
    buildFarms();
    while (Q--) {
        int a, b; cin >> a >> b;
        notifyFJ(a,b);
    }
}
*/

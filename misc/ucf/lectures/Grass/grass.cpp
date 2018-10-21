#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <deque>
using namespace std;

ofstream fout("grass.out");
ifstream fin("grass.in");
int n, m;
const int maxn = 100005;
const int INF = 2000000000;
vector<int> inn[maxn], out[maxn];
vector<int> condense[maxn], rev[maxn];
bool visited[maxn];
int sz[maxn];
int comp[maxn];
deque<int> L;

void visit(int now) {
    if (!visited[now]) {
        visited[now] = true;
        for (int j: inn[now]) {
            visit(j);
        }
        L.push_front(now);
    }
}

void assign(int u, int root) {
    if (comp[u] == 0) {
        comp[u] = root;
        sz[root]++;
        for (int j: out[u]) {
            assign(j,root);
        }
    }
}

int dp[2][maxn];
int f(int on, int i) {
    if (dp[on][i] != -1) {
        return dp[on][i];
    }
    if (on == 0 && i == 1) {
        return dp[on][i] = 0;
    }
    dp[on][i] = -2;
    if (on == 1) {
        for (int j: rev[i]) {
            int te = f(0,j);
            if (te != -2) {
                dp[on][i] = max(dp[on][i],sz[i] + te);
            }
        }
    }
    for (int j: condense[i]) {
        int te = f(on,j);
        if (te != -2) {
            dp[on][i] = max(dp[on][i],sz[i] + te);
        }
    }
    return dp[on][i];
}

int main() 
{
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        inn[u].push_back(v);
        out[v].push_back(u);
    }
    //Kosaraju
    for (int i = 1; i <= n; i++) {
        visit(i);
    }
    for (int u: L) {
        assign(u,u);
    }
    //create condensation graph
    for (int i = 1; i <= n; i++) {
        for (int j: inn[i]) {
            if (comp[i] == comp[j]) continue;
            condense[comp[i]].push_back(comp[j]);
            rev[comp[j]].push_back(comp[i]);
        }
    }
    //do dp
    memset(dp,-1,sizeof(dp));
    int c1 = comp[1];
    int ans = f(1,c1);
    cout << (ans == -2 ? sz[c1] : ans) << '\n';
    
    

	return 0;
}


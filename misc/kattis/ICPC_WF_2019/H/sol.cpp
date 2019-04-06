#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//each component has at most 1 cycle
const int maxn = 5e5+5;
const int maxk = 20;
int n, k;
int to[maxn];
vector<int> bi[maxn];
bool vis[maxn];
int inn[maxn];

int ans[maxn];

void dfs(int i, vector<int>& comp) {
    vis[i] = true;
    comp.push_back(i);
    for (int j: bi[i]) {
        if (vis[j]) continue;
        dfs(j,comp);
    }
}

int ord[maxn];
vector<int> rev[maxn]; //store the reverse edges
int jmp[maxk][maxn];

int walk(int i, int steps) {
    for (int k = maxk - 1; k >= 0; k--) {
        if (steps & (1<<k)) {
            i = jmp[k][i];
            if (i == -1) return i;
        }
    }
    return i;
}

int sub[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> to[i];
        rev[to[i]].push_back(i);
        bi[i].push_back(to[i]);
        bi[to[i]].push_back(i);
        inn[to[i]]++;
    }
    memset(ord,-1,sizeof ord);
    memset(jmp,-1,sizeof jmp);
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        vector<int> comp;
        dfs(i,comp);
        int sz = comp.size();
        queue<int> q; //TOPSORT
        vector<int> r; //order of topsort
        for (int j: comp) if (inn[j] == 0) q.push(j);
        while (!q.empty()) {
            int f = q.front(); q.pop();
            ord[f] = r.size();
            r.push_back(f);
            if (--inn[to[f]] == 0) {
                q.push(to[f]);
            }
        }
        if (r.empty()) {
            //full cycle
            for (int j: comp) {
                ans[j] = min(sz,k);
            }
        }
        else {
            int cycStart = to[r.back()];
            vector<int> cycle;
            if (cycStart != 0) {
                while (true) {
                    r.push_back(to[r.back()]);
                    if (to[r.back()] == cycStart) break;
                }
            }
            for (int j: r) {
                if (j != r.back()) {
                    jmp[0][j] = to[j];
                }
            }
            for (int k = 1; k < maxk; k++) {
                for (int j: r) {
                    if (jmp[k-1][j] == -1) jmp[k][j] = -1;
                    else jmp[k][j] = jmp[k-1][jmp[k-1][j]];
                }
            }
            for (int j: r) {
                int s = walk(j,k+1);
                if (s == -1) continue;
                else sub[s]++;
            }
        }
    }
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
void amax(int& a, int b) {
    a = max(a,b);
}

int take[maxn], skip[maxn];
int child[maxn];
void dfs(int i, int p) {
    int c = 0;
    for (int j: adj[i]) if (j != p) {
        dfs(j,i);
        c++;
    }
    child[i] = c;
    for (int j: adj[i]) if (j != p) {
        amax(skip[i],take[j]);

        amax(take[i],take[j]+c-1);
        amax(take[i],skip[j]+c);
    }
    //cout << i << ": " << take[i] << ' ' << skip[i] << '\n';
}

int ans = 0;

void reroot(int i, int p) {
    amax(ans,take[i]);
    int c = child[i] + (i!=p);
    multiset<int> ms_take, ms_skip;
    for (int j: adj[i]) if (j != p || i != p) {
        ms_take.insert(take[j]+c-1);
        ms_take.insert(skip[j]+c);
        ms_skip.insert(take[j]);
    }
    for (int j: adj[i]) if (j != p) {
        int old_take_i = take[i];
        int old_skip_i = skip[i];
        int old_take_j = take[j];
        int old_skip_j = skip[j];

        ms_take.erase(ms_take.find(take[j]+c-1));
        ms_take.erase(ms_take.find(skip[j]+c));
        ms_skip.erase(ms_skip.find(take[j]));

        take[i] = ms_take.empty() ? 0 : *ms_take.rbegin()-1;
        skip[i] = ms_skip.empty() ? 0 : *ms_skip.rbegin()-1;
        int cj = child[j]+1;
        take[j]++;
        amax(take[j],max(take[i]+cj-1,skip[i]+cj));
        amax(skip[j],take[i]);

        reroot(j,i);

        take[i] = old_take_i;
        skip[i] = old_skip_i;
        take[j] = old_take_j;
        skip[j] = old_skip_j;

        ms_take.insert(take[j]+c-1);
        ms_take.insert(skip[j]+c);
        ms_skip.insert(take[j]);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int root = rand() % n + 1;
    dfs(root,root);
    reroot(root,root);
    cout << ans << '\n';
}

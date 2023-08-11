#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
const int MOD = 2520;
int n, k[maxn];
vector<int> adj[maxn];

int norm(int x) {
    x = (ll)(x+MOD*400000) % MOD;
    return x;
}

//very large directed graph (functional graph), but finite
//therefore it will end up in a cycle
//READ THE CONSTRAINTS!!!

pair<int,int> nxt(int i, int c) {
    c = norm(c+k[i]);
    return {adj[i][c%adj[i].size()],c};  
}

int ans[maxn][MOD]; //0 = untouched, -1 = on stack, > 0 = solved
vector<pair<int,int>> st;

void dfs(int i, int c) {
    if (ans[i][c] > 0) return;
    ans[i][c] = -1;
    st.push_back({i,c});
    auto nx = nxt(i,c);
    if (ans[nx.first][nx.second] > 0) {
        ans[i][c] = ans[nx.first][nx.second];
    }
    else if (ans[nx.first][nx.second] == -1) {
        //on stack, found cycle
        set<int> seen;
        for (int i = st.size()-1; i >= 0; i--) {
            seen.insert(st[i].first);
            if (st[i] == nx) break;
        }
        ans[i][c] = seen.size();
    }
    else if (ans[nx.first][nx.second] == 0) {
        dfs(nx.first,nx.second);
        ans[i][c] = ans[nx.first][nx.second];
    }
    st.pop_back();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> k[i];
        k[i] = norm(k[i]);
    }
    for (int i = 1; i <= n; i++) {
        int f; cin >> f;
        while (f--) {
            int ai; cin >> ai;
            adj[i].push_back(ai);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int c = 0; c < MOD; c++) {
            if (ans[i][c] == 0) {
                dfs(i,c);
            }
        }
    }
    //answer queries
    int q; cin >> q;
    while (q--) {
        int i, c; cin >> i >> c;
        c = norm(c);
        cout << ans[i][c] << '\n';
    }
}


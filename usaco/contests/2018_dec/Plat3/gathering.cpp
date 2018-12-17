#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, M;
vector<int> adj[maxn], dir[maxn];
int mark[maxn];

bool dfs(int i, int p, int x) {
    if (i == x) return true;
    bool is = false;
    for (int j: adj[i]) {
        if (j == p) continue;
        is |= dfs(j,i,x);    
        if (is) break;
    }
    return is;
}

void fillDFS(int i, int p) {
    mark[i]++;
    for (int j: adj[i]) {
        if (j == p) continue;
        fillDFS(j,i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("gathering.in","r",stdin); freopen("gathering.out","w",stdout);
    cin >> N >> M;
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        dir[a].push_back(b);
    }
    for (int i = 1; i <= N; i++) {
        for (int x: dir[i]) {
            for (int j: adj[i]) {
                bool is = dfs(j,i,x);
                if (is) {
                    fillDFS(j,i);
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        cout << (mark[i] == M ? 1 : 0) << '\n';
    }

    return 0;
}


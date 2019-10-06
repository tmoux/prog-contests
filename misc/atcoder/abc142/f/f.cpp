#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int N, M;
vector<int> adj[maxn];

bool found = false;
vector<int> ans;

vector<int> st;
int t[maxn];
bool vis[maxn];
int pt = 1;
void dfs(int i, int ps) { //pt is start time of dfs
    if (found) return;
    st.push_back(i);
    t[i] = pt++;
    sort(adj[i].begin(),adj[i].end(),[](int a, int b) {
            return t[a] > t[b];
            });
    for (int j: adj[i]) {
        if (vis[j]) continue;
        if (t[j] >= ps) {
            //found cycle
            found = true;
            while (!st.empty()) {
                ans.push_back(st.back());
                st.pop_back();
                if (ans.back() == j) break;
            }
        }
        else {
            dfs(j,ps);
        }
    }
    st.pop_back();
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }
    int time = 1;
    for (int i = 1; i <= N; i++) {
        if (!found) dfs(i,time,time);
        for (int j = 1; j <= N; j++) {
            if (t[j] > 0) {
                vis[j] = true;
            }
            t[j] = 0;
        }
    }
    if (!found) {
        cout << -1 << '\n';
    }
    else {
        cout << ans.size() << '\n';
        for (int i: ans) {
            cout << i << '\n';
        }
    }
}


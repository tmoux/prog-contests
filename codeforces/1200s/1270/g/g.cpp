#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int a[maxn];
int n;

vector<int> adj[maxn];

stack<int> st;
int vis[maxn]; //1 = on stack
vector<int> ans;
void dfs(int i) {
    vis[i] = 1;
    st.push(i);
    if (vis[a[i]]) {
        while (true) {
            int t = st.top();
            ans.push_back(t);
            st.pop();
            if (t == a[i]) break;
        }
        return;
    }
    dfs(a[i]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        while (!st.empty()) st.pop();
        for (int i = 1; i <= n; i++) {
            vis[i] = 0;
            cin >> a[i];
            a[i] = i-a[i];
            adj[i].push_back(a[i]);
        }
        ans.clear();
        dfs(1);
        cout << ans.size() << '\n';
        for (auto i: ans) {
            cout << i << ' ';
        }
        cout << '\n';
   }
}


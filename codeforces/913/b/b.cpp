#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
vector<int> adj[1005];
int cnt[1005];

bool poss = true;

void dfs(int i) {
    if (adj[i].empty()) cnt[i] = 1;
    else {
        int c = 0;
        for (int j: adj[i]) {
            dfs(j);
            if (cnt[j]) c++;
        }
        if (c < 3) {
            poss = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int pi; cin >> pi;
        adj[pi].push_back(i);
    }
    dfs(1);
    cout << (poss ? "Yes": "No") << '\n';
}


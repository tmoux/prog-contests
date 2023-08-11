#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
int a[maxn];

set<int> adj[maxn];

bool use[maxn];

void dfs(int i, int p) {
    for (int j: adj[i]) {
        if (j == p) continue;
        assert(j != i);
        cout << i << ' ' << j << '\n';
        dfs(j,i);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n-1; i++) {
        cin >> a[i];
    }
    int curr = n;
    use[n] = true;
    int u = -1;
    for (int i = 1; i <= n-1; i++) {
        //cout << i << ": " << a[i] << endl;
        if (use[a[i]]) {
            while (use[curr]) {
                curr--;
            }
            if (curr < 1) {
                cout << -1 << '\n';
                return 0;
            }
            use[curr] = true;
            u = a[i];
            adj[u].insert(curr);
            //cout << "adding edge " << u << ' ' << curr << endl;
        }
        else {
            use[a[i]] = true;
            if (u != -1) {
                adj[u].erase(curr);
                //cout << "remove edge " << u << ' ' << curr << endl;
                adj[u].insert(a[i]);
                //cout << "adding edge " << u << ' ' << a[i] << endl;
            }
            u = a[i];
            adj[u].insert(curr);
            //cout << "adding edge " << u << ' ' << curr<< endl;
        }
    }
    //output
    cout << a[1] << '\n';
    dfs(a[1],a[1]);
    /*
    for (int i = 1; i <= n; i++) {
        for (int j: adj[i]) {
            cout << i << ' ' << j << '\n';
        }
    }
    */
}


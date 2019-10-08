#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 23;
int n, m, adj[N][N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u][v] = adj[v][u] = 1;
    }
    random_device rd;
    mt19937 gen(rd());
    vector<int> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }
    int ans = n;
    vector<int> result;
    for (int qq = 0; qq < 10000; qq++) {
        shuffle(v.begin(),v.end(),gen);
        vector<bool> seen(n+1,false);
        vector<bool> inClique(n+1,false);
        vector<int> clique;
        for (int j: v) {
            if (seen[j]) continue;
            clique.push_back(j);
            inClique[j] = true;
            seen[j] = true;
            for (int k = 1; k <= n; k++) {
                if (!adj[j][k]) seen[k] = true;
            }
        }
        /*
        cout << "curr clique: ";
        for (int i: clique) {
            cout << i << ' ';
        }
        cout << '\n';
        */
        int steps = 0;
        vector<int> res;
        //actually just do O(N^3) greedy
        while (clique.size() < n) {
            steps++;
            pair<int,int> best = {-1,-1};
            for (int i: clique) {
                int deg = 0;
                for (int j = 1; j <= n; j++) {
                    if (adj[i][j] && !inClique[j]) {
                        deg++;
                    }
                }
                best = max(best,{deg,i});
            }
            res.push_back(best.second);
            for (int i = 1; i <= n; i++) {
                if (adj[best.second][i] && !inClique[i]) {
                    //cout << steps << ' ' << best.second << ": " << "adding " << i << '\n';
                    clique.push_back(i);
                    inClique[i] = true;
                }
            }
        }
        /*
        assert(steps == res.size());
        cout << "steps = " << steps << '\n';
        for (int i: res) {
            cout << i << ' ';
        }
        cout << '\n';
        */
        if (steps < ans) {
            ans = steps;
            result = res;
        }
    }
    assert(ans == result.size());
    cout << ans << '\n';
    for (int i: result) {
        cout << i << ' ';
    }
    cout << '\n';
}


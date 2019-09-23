#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
vector<int> adj[8];

int label[8];

int ans = 0;
void recurse(int i) {
    if (i == n+1) {
        //check if valid
        /*
        cout << "c: ";
        for (int j = 1; j <= n; j++) {
            cout << label[j] << ' ';
        }
        cout << '\n';
        */
        int nonZero = 0;
        set<pair<int,int>> s;
        for (int k = 1; k <= n; k++) {
            for (int j: adj[k]) {
                pair<int,int> p = {min(label[k],label[j]),max(label[k],label[j])};
                if (s.count(p)) {
                    continue;
                }
                else {
                    s.insert(p);
                    nonZero++;
                }
            }
        }
        ans = max(ans,nonZero);
        /*
        if (nonZero == 15) {
            for (int j = 1; j <= n; j++) {
                cout << label[j] << ' ';
            }
            cout << '\n';
            for (auto p: s) {
                cout << p.first << ' ' << p.second << '\n';
            }
            exit(0);
        }
        */
        return;
    }
    for (int k = 1; k <= 6; k++) {
        label[i] = k;
        recurse(i+1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }
    recurse(1);
    ans = min(ans,m);
    cout << ans << '\n';
}


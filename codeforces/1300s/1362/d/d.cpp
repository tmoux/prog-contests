#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n, m;
vector<int> adj[maxn];
int t[maxn];
vector<int> v[maxn];
int c[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        v[t[i]].push_back(i);
    }
    vector<int> ord;
    for (int iter = 1; iter <= n; iter++) {
        for (int i: v[iter]) {
            set<int> s;
            int mex = 1;
            for (int j: adj[i]) if (c[j]) {
                s.insert(c[j]);
                while (s.count(mex)) mex++;
            }
            if (mex == t[i]) {
                c[i] = mex;
                ord.push_back(i);
            }
            else {
                cout << -1 << '\n';
                return 0;
            }
        }
    }
    for (auto i: ord) {
        cout << i << ' ';
    }
    cout << '\n';
}

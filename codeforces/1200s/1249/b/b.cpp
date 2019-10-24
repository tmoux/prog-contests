#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5+5;
int n;
int p[N];
int cyc[N];

void dfs(int i, int orig, int c) {
    if (i == orig) {
        cyc[i] = c;
        return;
    }
    dfs(p[i],orig,c+1);
    cyc[i] = cyc[p[i]];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            cyc[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            if (cyc[i] == 0) {
                dfs(p[i],i,1);
            }
        }
        for (int i = 1; i <= n; i++) {
            cout << cyc[i] << ' ';
        }
        cout << '\n';
    }
}


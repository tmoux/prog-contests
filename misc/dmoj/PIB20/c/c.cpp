#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int comp[maxn], par[maxn];
int flip[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    int pt = 0;
    int i = 1;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            comp[i] = ++pt;
            ++i;
        }
        else if (t == 2) {
            comp[i] = pt;
            par[i] = 1^par[i-1];
            flip[pt] ^= 1;
            ++i;
        }
        else {
            int x; cin >> x;
            cout << (flip[comp[x]]^par[x] ? 0 : 1) << '\n';
        }
    }
}


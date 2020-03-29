#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5, M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int n, m;
set<int> S;
int ex2[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ex2[0] = 1;
    for (int i = 1; i < maxn; i++) {
        ex2[i] = mult(ex2[i-1],2);
    }
    cin >> n >> m;
    string s; cin >> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            S.insert(i);
        }
        else {
            madd(ans,ex2[n-i-1]);
        }
    }
    while (m--) {
        int l, r; cin >> l >> r;
        --l; --r;
        for (auto it = S.lower_bound(l); it != S.end();) {
            if (*it > r) break;
            else {
                madd(ans,ex2[n-*it-1]);
                S.erase(it++);
            }
        }
        cout << ans << '\n';
    }
}


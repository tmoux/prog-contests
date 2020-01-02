#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int pre[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int n = s.size();
    for (int i = 1; i <= n; i++) {
        pre[i] = s[i-1] == '1';
        pre[i] += pre[i-1];
    }
    for (int k = n; k >= 1; k--) {
        if (pre[k]-pre[n-k] == 0 || pre[k]-pre[n-k] == 2*k-n) {
            cout << k << '\n';
            return 0;
        }
    }
}


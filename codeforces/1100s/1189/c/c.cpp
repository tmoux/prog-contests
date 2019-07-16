#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, s[maxn];
int q;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i-1];
    }
    cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << (s[r]-s[l-1])/10 << '\n';
    }
}


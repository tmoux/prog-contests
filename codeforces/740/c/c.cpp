#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    int mn =  n + 5;
    while (m--) {
        int l, r; cin >> l >> r;
        mn = min(mn,r-l+1);
    }
    cout << mn << '\n';
    for (int i = 0; i < n; i++) {
        cout << (i%mn) << ' ';
    }
    cout << '\n';
}


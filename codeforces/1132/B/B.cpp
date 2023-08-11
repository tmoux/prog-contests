#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m, a[maxn];


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    ll total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
    }
    sort(a,a+n);
    cin >> m;
    vector<int> q(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i];
        int x = q[i];
        cout << (total - a[n-x]) << '\n';
    }

    return 0;
}


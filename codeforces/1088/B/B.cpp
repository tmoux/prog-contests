#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, k, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a,a+n);
    int idx = 0;
    int sub = 0;
    while (k--) {
        while (a[idx] == sub) {
            idx++;
            if (idx >= n) break;
        }
        if (idx >= n) {
            cout << 0 << '\n';
            continue;
        }
        cout << a[idx]-sub << '\n';
        sub += (a[idx]-sub);
        idx++;
    }

    return 0;
}


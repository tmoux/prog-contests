#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, l[maxn], r[maxn], a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> l[i];
    for (int i = 1; i <= n; i++) cin >> r[i];
    for (int i = 1; i <= n; i++) a[i] = n - l[i] - r[i];
    for (int i = 1; i <= n; i++) {
        if (!(1 <= a[i] && a[i] <= n)) {
            cout << "NO" << '\n';
            return 0;
        }
        int ll = 0, rr = 0;
        for (int j = i - 1; j >= 1; j--) {
            if (a[j] > a[i]) ll++;
        }
        for (int j = i + 1; j <= n; j++) {
            if (a[j] > a[i]) rr++;
        }
        if (!(ll == l[i] && rr == r[i])) {
            cout << "NO" << '\n';
            return 0;
        }
    }
    cout << "YES" << '\n';
    for (int i = 1; i <= n; i++) cout << a[i] << ' ';

    return 0;
}


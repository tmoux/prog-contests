#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
        if (!a[i] && a[i-1] && a[i+1]) {
            ans++;
            a[i+1] = 0;
        }
    }
    cout << ans << '\n';

    return 0;
}


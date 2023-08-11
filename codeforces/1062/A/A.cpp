#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, a[maxn];
int r[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[0] = 0; a[n+1] = 1001;
    int ri = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i-1] == a[i]-1 && a[i+1] == a[i]+1) {
            r[i] = r[i-1] + 1;
        }
        else r[i] = 0;
        ri = max(ri,r[i]);
    }
    cout << ri << '\n';

    return 0;
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n, a[maxn];
bool used[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a,a+n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        else {
            ans++;
            for (int j = 0; j < n; j++) {
                if (a[j] % a[i] == 0) used[j] = true;
            }
        }
    }
    cout << ans << '\n';
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
const int M = 998244353;
int n, d[maxn];
int cnt[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    sort(d,d+n);
    if (d[0] != 0 || (n > 1 && d[1] == 0)) {
        cout << 0 << '\n';
        return 0;
    }
    cnt[0] = 1;
    int ans = 1;
    for (int i = 1; i < n; i++) {
        ans = (1LL*ans*cnt[d[i]-1]) % M;                
        cnt[d[i]]++;
    }
    cout << ans << '\n';
}


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cnt[105];
int ceil(int a, int b) {
    return (a%b == 0 ? a/b:a/b+1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        cnt[ai]++;
    }
    int mx = 0;
    for (int i = 1; i <= 100; i++) {
        if (cnt[i] > 0) {
            mx = max(mx,ceil(cnt[i],k));
        }
    }
    int ans = 0;
    for (int i = 1; i <= 100; i++) {
        if (cnt[i] > 0) {
            ans += mx*k-cnt[i];        
        }
    }
    cout << ans << '\n';

    return 0;
}


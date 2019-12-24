#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n, m;
int a[maxn], b[2*maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(a,a+n);
    sort(b,b+n);
    for (int i = 0; i < n; i++) {
        b[i+n] = b[i];
    }
    int ans = 1e9+9;
    for (int i = 0; i < n; i++) {
        int diff = (b[i]-a[0]+m)%m;
        bool poss = true;
        for (int j = 0; j < n; j++) {
            if ((a[j]+diff)%m != b[i+j]) {
                poss = false;
                break;
            }
        }
        if (poss) ans = min(ans,diff);
    }
    cout << ans << endl;
}

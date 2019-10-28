#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m, a, c, x_0;
int x[1000006];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> a >> c >> x_0;
    x[0] = x_0;
    for (int i = 1; i <= n; i++) {
        x[i] = (1LL*a*x[i-1]+c) % m;
        //cout << x[i] << ' ';
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int target = x[i];
        int lo = 1, hi = n;
        bool poss = false;
        while (lo <= hi) {
            int mid = (lo+hi)/2;
            if (x[mid] == target) {
                poss = true;
                break;
            }
            else if (x[mid] < target) {
                lo = mid+1;
            }
            else {
                hi = mid-1;
            }
        }
        if (poss) ans++;
    }
    cout << ans << '\n';
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
int a[2*maxn];
int balance[2*maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= 2*n; i++) {
            cin >> a[i];
            if (a[i] == 2) a[i] = -1;
        }
        for (int i = 0; i <= 2*n+5; i++) {
            balance[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            balance[i] = balance[i-1] + a[i];
        }
        for (int i = 2*n; i > n; i--) {
            balance[i] = balance[i+1] + a[i];
        }
        map<int,int> lastSeen;
        for (int i = 0; i <= n; i++) {
            lastSeen[balance[i]] = i;
        }
        int ans = 2*n;
        for (int i = n+1; i <= 2*n+1; i++) {
            int target = -balance[i];
            if (lastSeen.count(target)) {
                int left = n - lastSeen[target];
                int right = i-(n+1);
                ans = min(ans,left+right);
            }
        }
        cout << ans << endl;
    }
}


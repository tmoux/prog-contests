#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
int a[2*maxn];
int tin[maxn], tout[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        tin[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[n+i];
        tout[a[n+i]] = n+i;
    }
    int ans = 0;
    int maxSeen = -1;
    for (int i = 0; i < n; i++) {
        if (tout[a[i]] < maxSeen) {
            ans++;
        }
        maxSeen = max(maxSeen,tout[a[i]]);
    }
    cout << ans << '\n';
}


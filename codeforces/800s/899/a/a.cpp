#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int c1 = 0, c2 = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (ai == 1) c1++;
        else c2++;
    }
    int ans = min(c1,c2);
    c1 -= ans;
    ans += c1/3;
    cout << ans << '\n';
}


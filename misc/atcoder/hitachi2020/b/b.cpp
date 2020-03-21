#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, m; cin >> a >> b >> m;
    vector<int> A(a), B(b);
    int mnA = 2e9, mnB = 2e9;
    for (int i = 0; i < a; i++) {
        cin >> A[i];
        mnA = min(mnA,A[i]);
    }
    for (int i = 0; i < b; i++) {
        cin >> B[i];
        mnB = min(mnB,B[i]);
    }
    int ans = mnA+mnB;
    for (int i = 0; i < m; i++) {
        int x, y, c; cin >> x >> y >> c;
        --x;
        --y;
        int tr = A[x] + B[y] - c;
        ans = min(ans,tr);
    }
    cout << ans << endl;
}


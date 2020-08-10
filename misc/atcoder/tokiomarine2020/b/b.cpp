#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll A, B, V, W; cin >> A >> V >> B >> W;
    if (A == B) {
        cout << "YES\n";
        return 0;
    }
    if (W >= V) {
        cout << "NO\n";
        return 0;
    }
    ll dist = abs(A-B);
    ll vel = abs(V-W);
    ll T; cin >> T;
    if (dist <= T*vel) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }
}

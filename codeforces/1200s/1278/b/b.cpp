#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        int d = abs(a-b);
        for (int x = 0; ; x++) {
            if (((x*(x+1)/2)&1) == (d&1) && (x*(x+1)/2 >= d)) {
                cout << x << '\n';
                break;
            }
        }
    }
}


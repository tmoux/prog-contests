#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        cout << (a == b ? 0 : ((a<b)^((a+b)&1)) ? 2 : 1) << endl;
    }
}


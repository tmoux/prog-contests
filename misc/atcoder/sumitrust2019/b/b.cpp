#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i <= 50000; i++) {
        int m = (int)(floor((double)(1.08)*i));
        if (m == n) {
            cout << i << endl;
            return 0;
        }
    }
    cout << ":(\n";
}


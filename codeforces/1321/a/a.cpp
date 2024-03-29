#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ceil(int a, int b) {
    return (a+b-1)/b;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> r(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int c0 = 0, c1 = 0;
    for (int i = 0; i < n; i++) {
        if (r[i] == 1 && b[i] == 0) {
            c0++;
        }
        else if (r[i] == 0 && b[i] == 1) {
            c1++;
        }
    }
    if (!c0) {
        cout << -1 << endl;
    }
    else {
        //ceil(c1+1,c0) = (c1+1+c0-1)/c0 = (c1+c0)/c0
        cout << (c1+c0)/c0 << endl;
    }
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int a, b; cin >> a >> b;
    for (int i = 1; i <= 3; i++) {
        if (i == a || i == b) continue;
        cout << i << endl;
    }
}

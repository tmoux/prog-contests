#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << "1000 20" << '\n';
    for (int i = 0; i < 1000; i++) {
        int r = rand() % 20 + 1;
        cout << r << ' ';
    }
    cout << '\n';
    int q = 1000;
    cout << q << '\n';
    for (int i = 0; i < q; i++) {
        int l = rand() % 1000 + 1;
        int r = rand() % 1000 + 1;
        if (l > r) swap(l,r);
        cout << l << ' ' << r << '\n';
    }
}


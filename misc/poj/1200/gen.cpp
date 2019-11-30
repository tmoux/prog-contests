#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << n/2 << ' ' << 26 << '\n';
    for (int i = 0; i < n; i++) {
        char c = 'a' + (rand()%26);
        cout << c;
    }
    cout << '\n';
}


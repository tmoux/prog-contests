#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string v = "aeiou";

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int k; cin >> k;
    for (int i = 5; i*i <= k; i++) {
        if (k % i == 0 && k/i >= 5) {
            int j = k/i;
            for (int r = 0; r < i; r++) {
                for (int c = 0; c < j; c++) {
                    cout << v[(r+c)%5];
                }
            }
            cout << endl;
            return 0;
        }
    }
    cout << -1 << '\n';
}


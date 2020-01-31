#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int cnt = 0;
    for (int i = 1; i <= 40; i++) {
        for (int j = 1; j <= 40; j++) {
            if (i*j <= 40) cnt++;
        }
    }
    cout << cnt << '\n';
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 20; j++) {
            bitset<5> x(i), y(j);
            //cout << x << ' ' << y << ": " << 
            if ((i+j) == (i^j)) cout << i << ' ' << j << ": " << (i+j) << ' ' << (i^j) << '\n';
        }
    }
}


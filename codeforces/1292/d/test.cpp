#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool isPrime(int i) {
    for (int j = 2; j*j <= i; j++) {
        if (i % j == 0) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int k = 5000;
    int sum = 0;
    for (int i = 2; i <= 5000; i++) {
        if (isPrime(i)) {
            int cnt = 0;
            int mult = i;
            while (k/mult > 0) {
                cnt += k/mult;
                mult *= i;
            }
            cout << i << ": " << cnt << endl;
            sum += cnt;
        }
    }
    cout << sum << endl;
}


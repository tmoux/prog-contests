#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n == 1) {
            cout << "FastestFinger\n";
        }
        else if (n == 2) {
            cout << "Ashishgup\n";
        }
        else if (n&1) {
            cout << "Ashishgup\n";
        }
        else {
            int s = 0;
            while (n % 2 == 0) {
                n /= 2;
                s++;
            }
            if (n == 1) {
                cout << "FastestFinger\n";
            }
            else if (s > 1) {
                cout << "Ashishgup\n";
            }
            else {
                bool isPrime = true;
                for (int i = 2; i*i <= n; i++) {
                    if (n % i == 0) {
                        isPrime = false;
                        break;
                    }
                }
                cout << (isPrime ? "FastestFinger" : "Ashishgup") << '\n';
            }
        }
    }
}

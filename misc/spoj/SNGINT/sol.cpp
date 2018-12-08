#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int arr[200];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n < 10) {
            if (n == 0) {
                n += 10;
            }
            cout << n << '\n';
        }
        else {
            int k = 0;
            for (int i = 9; i >= 2; i--) {
                while (n % i == 0) {
                    arr[k++] = i;
                    n /= i;
                }
            }
            if (n > 1) {
                cout << -1 << '\n';
            }
            else {
                for (int i = k-1; i >= 0; i--) {
                    cout << arr[i];
                }
                cout << '\n';
            }
        }
    }

    return 0;
}


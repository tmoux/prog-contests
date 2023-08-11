#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
ll a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (n == 1) {
        cout << "1 1\n";
        cout << -a[0] << '\n';
        cout << "1 1\n";
        cout << 0 << '\n';
        cout << "1 1\n";
        cout << 0 << '\n';
        return 0;
    }
    cout << 1 << ' ' << n-1 << '\n';
    for (int i = 0; i < n-1; i++) {
        ll x = a[i] % n;
        cout << (x*(n-1)) << ' ';
        a[i] += x*(n-1);
    }
    cout << '\n';
    cout << n << ' ' << n << '\n';
    cout << ((a[n-1]%n)*(n-1)) << '\n';
    a[n-1] += (a[n-1]%n)*(n-1);
    cout << 1 << ' ' << n << '\n';
    for (int i = 0; i < n; i++) {
        cout << -a[i] << ' ';
    }
    cout << '\n';
    /*
    cout << "final: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
    */
}

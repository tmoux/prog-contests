#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
using ll = long long;

const int maxn = 1e6+6;
int n, m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < (m)/2; i++) {
        for (int j = 0; j < n; j++) {
            cout << (j+1) << ' ' << (i+1) << '\n';
            cout << (n-j) << ' ' << (m-i) << '\n';
        }
    }
    if (m&1) {
        for (int j = 0; j < n/2; j++) {
            cout << (j+1) << ' ' << (m/2+1) << '\n';
            cout << (n-j) << ' ' << (m/2+1) << '\n';
        }
        if (n&1) {
            cout << (n/2+1) << ' ' << (m/2+1) << '\n';
        }
    }
}

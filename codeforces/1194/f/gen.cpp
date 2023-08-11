#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; ll T;
    cin >> n >> T;
    cout << n << ' ' << T << '\n';
    for (int i = 1; i <= n; i++) {
        int r = rand() % 10 + 1;
        cout << r << ' ';
    }
    cout << '\n';
}


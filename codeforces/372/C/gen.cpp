#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, d; cin >> n >> m >> d;
    cout << n << ' ' << m << ' ' << d << '\n';
    for (int i = 0; i < n; i++) {
        int a = (rand() % n + 1);
        int b = rand() % 1000000000 + 1;
        //int t = 30;
        int t = rand() % 1000000000 + 1;
        cout << a << ' ' << b << ' ' << t << '\n';
    }
}


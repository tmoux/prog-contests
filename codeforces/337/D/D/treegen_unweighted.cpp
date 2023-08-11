#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
bool used[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m, d; cin >> n >> m >> d;
    cout << n << ' ' << m << ' ' << d << '\n';
    for (int i = 0; i < m; i++) {
        int r = (rand() % n) + 1;
        while (used[r]) {
            r = (rand() % n) + 1;
        }
        used[r] = true;
        cout << r << '\n';
    }
    for (int i = 2; i <= n; i++) {
        int r = (rand() % (i-1)) + 1;
        cout << i << ' ' << r << '\n';
    }

    return 0;
}


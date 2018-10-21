#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;

void solve(int col, int r) {
            
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    if (n > m) swap(n,m);
    if (n == 1) {
        cout << (m/6*3 + max(m % 6 - 3, 0)<<1) << '\n';
    }
    else if (n == 2) {
        cout << (m == 2 ? 0 : m == 3 ? 4 : m == 7 ? 12 : m*2) << '\n';
    }
    else {
        cout << (1LL*n*m/2*2) << '\n';
    }

    return 0;
}

